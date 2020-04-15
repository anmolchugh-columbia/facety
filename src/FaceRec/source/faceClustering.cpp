//
// Created by Bhavya Gupta on 4/14/20.
//

#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <filesystem>
#include "../../Utilities/header/Constants.h"

using namespace dlib;
using namespace std;

// ----------------------------------------------------------------------------------------
template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = add_prev1<block<N,BN,1,tag1<SUBNET>>>;

template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2,2,2,2,skip1<tag2<block<N,BN,2,tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET>
using block  = BN<con<N,3,3,1,1,relu<BN<con<N,3,3,stride,stride,SUBNET>>>>>;

template <int N, typename SUBNET> using ares      = relu<residual<block,N,affine,SUBNET>>;
template <int N, typename SUBNET> using ares_down = relu<residual_down<block,N,affine,SUBNET>>;

template <typename SUBNET> using alevel0 = ares_down<256,SUBNET>;
template <typename SUBNET> using alevel1 = ares<256,ares<256,ares_down<256,SUBNET>>>;
template <typename SUBNET> using alevel2 = ares<128,ares<128,ares_down<128,SUBNET>>>;
template <typename SUBNET> using alevel3 = ares<64,ares<64,ares<64,ares_down<64,SUBNET>>>>;
template <typename SUBNET> using alevel4 = ares<32,ares<32,ares<32,SUBNET>>>;

using anet_type = loss_metric<fc_no_bias<128,avg_pool_everything<
        alevel0<
                alevel1<
                        alevel2<
                                alevel3<
                                        alevel4<
                                                max_pool<3,3,2,2,relu<affine<con<32,7,7,2,2,
                                                        input_rgb_image_sized<150>
                                                >>>>>>>>>>>>;

// ----------------------------------------------------------------------------------------

std::vector<matrix<rgb_pixel>> jitter_image(
        const matrix<rgb_pixel>& img
);

void getFaces(
        string resources_path_string,
        std::vector<int>& faceID,
        std::vector<matrix<rgb_pixel>>& faces,
        const std::vector<string>& imagePaths
);

std::unordered_map<int, std::vector<string>> getClusters(
        string resources_path_string,
        std::vector<int>& faceID,
        std::vector<matrix<rgb_pixel>>& faces,
        const std::vector<string>& imagePaths
);

// ----------------------------------------------------------------------------------------

// model1 : "http://dlib.net/files/shape_predictor_5_face_landmarks.dat.bz2"
// model2 : "http://dlib.net/files/dlib_face_recognition_resnet_model_v1.dat.bz2"

std::unordered_map<int, std::vector<string>> clustering(std::vector<string> imagePaths) try
{


    Constants fileConstants = Constants::getInstance();
    filesystem::path models = fileConstants.project_directory / "resources/model";
    string resources_path_string(models.c_str());

    std::vector<int> faceID(imagePaths.size(), 0);
    std::vector<matrix<rgb_pixel>> faces;

    getFaces(resources_path_string, faceID, faces, imagePaths);

    if (faces.size() == 0)
    {
        cout << "No faces found in image!" << endl;
        return {};
    }

    return getClusters(resources_path_string, faceID, faces, imagePaths);
}
catch (std::exception& e)
{
    std::unordered_map<int, std::vector<string>> answer;
    cout << e.what() << endl;
    return answer;
}


// ----------------------------------------------------------------------------------------

std::vector<matrix<rgb_pixel>> jitter_image(
        const matrix<rgb_pixel>& img
)
{
    // All this function does is make 100 copies of img, all slightly jittered by being
    // zoomed, rotated, and translated a little bit differently. They are also randomly
    // mirrored left to right.
    thread_local dlib::rand rnd;

    std::vector<matrix<rgb_pixel>> crops;
    for (int i = 0; i < 100; ++i)
        crops.push_back(jitter_image(img,rnd));

    return crops;
}

// ----------------------------------------------------------------------------------------
void getFaces(string resources_path_string, std::vector<int>& faceID, std::vector<matrix<rgb_pixel>>& faces, const std::vector<string>& imagePaths){

    frontal_face_detector detector = get_frontal_face_detector();
    shape_predictor sp;
    deserialize( resources_path_string + "/shape_predictor_5_face_landmarks.dat") >> sp;
    for (int i = 0; i < imagePaths.size(); i++)
    {
        matrix<rgb_pixel> img;
        load_image(img, imagePaths[i]);

        while(img.size() < 1800*1800)
            pyramid_up(img);

        for (auto face : detector(img)) {
            auto shape = sp(img, face);
            matrix<rgb_pixel> face_chip;
            extract_image_chip(img, get_face_chip_details(shape, 150, 0.25), face_chip);
            faces.push_back(move(face_chip));
            faceID[i]++;
        }
    }
}

// ----------------------------------------------------------------------------------------
std::unordered_map<int, std::vector<string>> getClusters(string resources_path_string, std::vector<int>& faceID, std::vector<matrix<rgb_pixel>>& faces, const std::vector<string>& imagePaths ){

    anet_type net;
    deserialize(resources_path_string + "/dlib_face_recognition_resnet_model_v1.dat") >> net;
    std::vector<matrix<float,0,1>> face_descriptors = net(faces);

    std::vector<sample_pair> edges;
    for (size_t i = 0; i < face_descriptors.size(); ++i)
    {
        for (size_t j = i; j < face_descriptors.size(); ++j)
        {
            if (length(face_descriptors[i]-face_descriptors[j]) < 0.6)
                edges.push_back(sample_pair(i,j));
        }
    }
    std::vector<unsigned long> labels;
    const auto num_clusters = chinese_whispers(edges, labels);

    // Now let's display the face clustering results on the screen.  You will see that it
    // correctly grouped all the faces.

    std::unordered_map<int, std::vector<string>> clusters;
    for (size_t cluster_id = 0; cluster_id < num_clusters; ++cluster_id)
    {
        int imageID = 0, sum = 0;
        for (size_t j = 0; j < labels.size(); ++j)
        {
            if (cluster_id == labels[j]){
                while(faceID[imageID]==0 || j>=faceID[imageID] + sum) {
                    sum += faceID[imageID];
                    imageID++;
                }
                clusters[cluster_id].push_back(imagePaths[imageID]);
            }

        }
    }
    return clusters;
}





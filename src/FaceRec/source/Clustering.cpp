//
// Created by Bhavya Gupta on 4/26/20.
//
#include <dlib/dnn.h>
#include <dlib/clustering.h>
#include <dlib/image_io.h>
#include <filesystem>
#include "../../FileExplorer/header/directoryIterator.h"
#include "../../FileExplorer/header/makeClusterDirectories.h"
#include <unordered_set>
#include <chrono>
//#include "src/FaceRec/header/Clustering.h"
#include "../header/Clustering.h"


using namespace dlib;
using namespace std;

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


std::unordered_map<int, std::vector<string>> Clustering :: cluster(){
    getFaces();
    oldFaceStartIndex = getOldFaces();
    return getClusters();
}

void Clustering :: getFaces(){

    for (size_t i = 0; i < imagePaths.size(); i++)
    {
        auto start = chrono::high_resolution_clock::now();
        int count = detectFaces(imagePaths[i]);
        faceID[i] += count;
        if(!count){
            no_faces.push_back(imagePaths[i]);
        }
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout <<"time taken to detect faces in  "<< imagePaths[i]<< " : "<<duration.count()/1000000<< endl;
    }

}
int Clustering :: getOldFaces(){

    std::vector<string> directoryPaths = list_all_directories(path_to_existing_clusters);
    sort(directoryPaths.begin(), directoryPaths.end());
    int start = 0;

    if(!directoryPaths.empty()) {
        oldFaceStartIndex = faces.size();
        start = 1;
    }

    for (size_t i = start; i < directoryPaths.size(); i++)
    {
        string imageName;
        for(size_t j=directoryPaths[i].size()-1; j>=0 && directoryPaths[i][j]!='/'; j--)
            imageName += directoryPaths[i][j];
        reverse(imageName.begin(), imageName.end());
        string imagePath = directoryPaths[i] + "/" + imageName + ".png";
        oldFacePaths.emplace_back(imagePath);
        detectFaces(imagePath);
    }
    return oldFaceStartIndex;
}

std::unordered_map<int, std::vector<string>> Clustering :: getClusters(){
    anet_type net;
    deserialize(resources_path_string + "/dlib_face_recognition_resnet_model_v1.dat") >> net;
    std::vector<matrix<float,0,1>> face_descriptors = net(faces);

    std::vector<sample_pair> edges;
    for (size_t i = 0; i < face_descriptors.size(); ++i)
    {
        for (size_t j = i; j < face_descriptors.size(); ++j)
        {
            if (length(face_descriptors[i]-face_descriptors[j]) < 0.6) {
                edges.push_back(sample_pair(i, j));
                cout<<i<<" "<<j<<endl;
            }
        }
    }
    std::vector<unsigned long> labels;
    const unsigned long num_clusters = chinese_whispers(edges, labels);

    // Now let's display create the face clustering.
    std::unordered_map<int, std::vector<string>> clusters;

    int global_cluster_count = 0;
    std::unordered_set<int> doneClusterIDs;

    //Lets make some cluster directories
    createClusterDirectories(path_to_existing_clusters, num_clusters);
    cout<<"directories created"<<endl;
    // Lets make the clusters for old faces first
    for(size_t oldFaceCurrentIndex=oldFaceStartIndex; oldFaceCurrentIndex<labels.size(); oldFaceCurrentIndex++){
        size_t cluster_id = labels[oldFaceCurrentIndex];
        doneClusterIDs.insert(cluster_id);
        int imageID = 0, sum = 0;
        for (size_t j = 0; j < oldFaceStartIndex; ++j)
        {
            if (cluster_id == labels[j]){
                while(faceID[imageID]==0 || j>=faceID[imageID] + sum) {
                    sum += faceID[imageID];
                    imageID++;
                }
                clusters[global_cluster_count].push_back(imagePaths[imageID]);
            }
        }
        global_cluster_count++;
    }

    global_cluster_count = oldFacePaths.size();
    unsigned int end = oldFaceStartIndex==-1?labels.size():oldFaceStartIndex;
    for (size_t cluster_id = 0; cluster_id < num_clusters; ++cluster_id)
    {
        bool flag = false;
        if (doneClusterIDs.find(cluster_id)==doneClusterIDs.end()){
            int imageID = 0, sum = 0;
            for (size_t j = 0; j < end; ++j)
            {
                if (cluster_id == labels[j]){
                    while(faceID[imageID]==0 || j>=faceID[imageID] + sum) {
                        sum += faceID[imageID];
                        imageID++;
                    }
                    clusters[global_cluster_count].push_back(imagePaths[imageID]);
                    if(!flag) {
                        flag = true;
                        string relative = to_string(global_cluster_count) + "/" +
                                          to_string(global_cluster_count) + ".png";
                        save_png(faces[j], path_to_existing_clusters / relative);
                    }
                }
            }
            doneClusterIDs.insert(cluster_id);
            global_cluster_count+=1;
        }
    }

    clusters[-1] = no_faces;
    return clusters;
}

int Clustering :: detectFaces(string imagePath){

    matrix<rgb_pixel> img;
    load_image(img, imagePath);

    if(img.size() < 1800*1800)
        pyramid_up(img);

    int count = 0;
    for (auto face : detector(img)) {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape, 150, 0.25), face_chip);
        faces.push_back(move(face_chip));
        count++;
    }
    return count;

}
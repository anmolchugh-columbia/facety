//
// Created by Bhavya Gupta on 4/26/20.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file

#include <filesystem>
#include <boost/test/included/unit_test.hpp>
#include "../src/FaceRec/header/Clustering.h"
#include "../src/FaceRec/source/Clustering.cpp"
#include "../src/FileExplorer/source/ImageIterator.cpp"
#include "../src/Utilities/source/ImageUtilities.cpp"
#include "../src/FileExplorer/source/ImageOrganizer.cpp"
#include "../src/FileExplorer/source/directoryIterator.cpp"
#include "../src/FileExplorer/source/makeClusterDirectories.cpp"
#include <boost/bind.hpp>

using namespace std;


BOOST_AUTO_TEST_SUITE(Cluster)
BOOST_AUTO_TEST_CASE(makeClusterDirectories1){
        std::vector<string> expected = {"/Users/bhavyagupta/Desktop/facety/resources/clusters/-1","/Users/bhavyagupta/Desktop/facety/resources/clusters/0", "/Users/bhavyagupta/Desktop/facety/resources/clusters/1", "/Users/bhavyagupta/Desktop/facety/resources/clusters/2", "/Users/bhavyagupta/Desktop/facety/resources/clusters/3"};
        sort(expected.begin(), expected.end());
        std::filesystem::path path = "/Users/bhavyagupta/Desktop/facety/resources/clusters";
        createClusterDirectories( path, 4);
        auto directoryPaths = list_all_directories(path);
        sort(directoryPaths.begin(), directoryPaths.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(directoryPaths.begin(), directoryPaths.end(),expected.begin(),expected.end());
    }
BOOST_AUTO_TEST_CASE(cluster1) {
    std::vector<string> imagePaths;
    imagePaths = {"/Users/bhavyagupta/Desktop/facety/resources/faces4/cat1.jpeg"};
    std::filesystem::path path = "/Users/bhavyagupta/Desktop/facety/resources/clusters";
    Clustering tester = Clustering(imagePaths, path);


    std::unordered_map<int, std::vector<string>> clusters = tester.cluster();
    std::unordered_map<int, std::vector<string>> expected;
    expected[0].push_back("/Users/bhavyagupta/Desktop/facety/resources/faces4/cat1.jpeg");
    expected[-1] = {};
    for(auto it = clusters.begin();it!=clusters.end();it++){
        int key = it->first;
        BOOST_CHECK_EQUAL_COLLECTIONS(it->second.begin(), it->second.end(),expected[key].begin(),expected[key].end());
    }
}

BOOST_AUTO_TEST_CASE(cluster2) {
        std::vector<string> imagePaths;
        imagePaths = {"/Users/bhavyagupta/Desktop/facety/resources/faces4/cat1.jpeg", "/Users/bhavyagupta/Desktop/facety/resources/faces4/tom.jpg"};
        std::filesystem::path path = "/Users/bhavyagupta/Desktop/facety/resources/clusters";
        Clustering tester = Clustering(imagePaths, path);


        std::unordered_map<int, std::vector<string>> clusters = tester.cluster();
        std::unordered_map<int, std::vector<string>> expected;
        expected[0].push_back("/Users/bhavyagupta/Desktop/facety/resources/faces4/cat1.jpeg");
        expected[1].push_back("/Users/bhavyagupta/Desktop/facety/resources/faces4/tom.jpg");
        expected[-1] = {};

        for(auto it = clusters.begin();it!=clusters.end();it++){
            int key = it->first;
            cout<<key<<endl;
            BOOST_CHECK_EQUAL_COLLECTIONS(it->second.begin(), it->second.end(),expected[key].begin(),expected[key].end());
        }
    }
BOOST_AUTO_TEST_CASE(cluster3) {
        std::vector<string> imagePaths;
        imagePaths = {"/Users/bhavyagupta/Desktop/facety/resources/faces4/dog1.jpeg"};
        std::filesystem::path path = "/Users/bhavyagupta/Desktop/facety/resources/clusters";
        Clustering tester = Clustering(imagePaths, path);

        std::unordered_map<int, std::vector<string>> clusters = tester.cluster();
        std::unordered_map<int, std::vector<string>> expected;
        expected[-1] = {"/Users/bhavyagupta/Desktop/facety/resources/faces4/dog1.jpeg"};
        for(auto it = clusters.begin();it!=clusters.end();it++){
            int key = it->first;
            BOOST_CHECK_EQUAL_COLLECTIONS(it->second.begin(), it->second.end(),expected[key].begin(),expected[key].end());
        }
}
BOOST_AUTO_TEST_CASE(cluster4) {
        std::vector<string> imagePaths;
        imagePaths = {"/Users/bhavyagupta/Desktop/facety/resources/faces4/kit_and_emilia1.jpeg"};
        std::filesystem::path path = "/Users/bhavyagupta/Desktop/facety/resources/clusters";
        Clustering tester = Clustering(imagePaths, path);

        std::unordered_map<int, std::vector<string>> clusters = tester.cluster();
        std::unordered_map<int, std::vector<string>> expected;

        expected[2].push_back("/Users/bhavyagupta/Desktop/facety/resources/faces4/kit_and_emilia1.jpeg");
        expected[3].push_back("/Users/bhavyagupta/Desktop/facety/resources/faces4/kit_and_emilia1.jpeg");
        expected[-1] = {};
        for(auto it = clusters.begin();it!=clusters.end();it++){
            int key = it->first;
            BOOST_CHECK_EQUAL_COLLECTIONS(it->second.begin(), it->second.end(),expected[key].begin(),expected[key].end());
        }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Directories)
BOOST_AUTO_TEST_CASE(ImageIterator1){
        std::vector<string> expected = {"/Users/bhavyagupta/Desktop/facety/resources/faces3/tom2.jpg"};
        const std::filesystem::path path = "/Users/bhavyagupta/Desktop/facety/resources/faces3";
        auto imagePaths = list_all_images(path);
        BOOST_CHECK_EQUAL_COLLECTIONS(imagePaths.begin(), imagePaths.end(),expected.begin(),expected.end());

    }
BOOST_AUTO_TEST_CASE(DirectoryIterator1){
        std::vector<string> expected = {"/Users/bhavyagupta/Desktop/facety/resources/faces4/faces5"};
        const std::filesystem::path path = "/Users/bhavyagupta/Desktop/facety/resources/faces4";
        auto directoryPaths = list_all_directories(path);
        BOOST_CHECK_EQUAL_COLLECTIONS(directoryPaths.begin(), directoryPaths.end(),expected.begin(),expected.end());
    }

BOOST_AUTO_TEST_CASE(ImageOrganizer0){
        std::unordered_set<string> expected;
        expected.insert("-1");
        expected.insert("0");
        std::unordered_map<int, std::vector<string>> clusters;
        clusters[0].push_back("/Users/bhavyagupta/Desktop/facety/resources/faces4/cat1.jpeg");
        clusters[-1] = {};

        auto names = getClusterNames(clusters);
//      BOOST_CHECK_EQUAL(expected == names , true);
        BOOST_TEST(expected == names, boost::test_tools::per_element());
    }
BOOST_AUTO_TEST_CASE(ImageOrganizer1){
        std::vector<string> expected = {"/Users/bhavyagupta/Desktop/facety/resources/clusters/0/cat1.jpeg", "/Users/bhavyagupta/Desktop/facety/resources/clusters/0/0.png"};
        std::unordered_map<int, std::vector<string>> clusters;
        clusters[0].push_back("/Users/bhavyagupta/Desktop/facety/resources/faces4/cat1.jpeg");
        clusters[-1] = {};
        std::filesystem::path path = "/Users/bhavyagupta/Desktop/facety/resources/clusters";
        populateClusters( path, clusters);
        path += "/0";
        auto imagePaths = list_all_images(path);
        BOOST_CHECK_EQUAL_COLLECTIONS(imagePaths.begin(), imagePaths.end(),expected.begin(),expected.end());
    }
BOOST_AUTO_TEST_SUITE_END()

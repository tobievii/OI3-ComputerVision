#include "ComputerVision.h"
#include "ComputerVisionModule.h"
#include "FaceAnalyzer.h"
#include "IVision.h"
#include "ICvAnalyzer.h"
#include "RaspiCamera.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <thread>
#include <unistd.h>

#define CASCADE_FILE_FACE ("./haarcascades/haarcascade_frontalface_alt.xml")
#define CASCADE_FILE_EYES ("./haarcascades/haarcascade_eye_tree_eyeglasses.xml")
#define IMAGE_COUNT (2000)
#define FACE_ANALYZER_SCALE_FACTOR (1.85f)
#define FACE_ANALYZER_NEIGHBOR_COUNT (2)

int main(int argc, char **argv)
{
    //Create camera
    ICvCamera *raspiCam = new RaspiCamera(320, 240);

    //Create face analyzer
    ICvAnalyze *faceAnalyzer = new FaceAnalyzer(CASCADE_FILE_FACE, FACE_ANALYZER_NEIGHBOR_COUNT, 
        FACE_ANALYZER_SCALE_FACTOR);

    //Create the vision
    IVision *computerVision = new ComputerVision(*raspiCam, *faceAnalyzer);

<<<<<<< HEAD
    ComputerVisionModule module(*raspiCam, *computerVision);

    //Sleep 10 seconds
    usleep(10000000);
=======
    for (size_t i = 0; i < IMAGE_COUNT; i++)
    {
        computerVision->ScanFaces();

        for (auto &face : computerVision->GetFaces())
        {
                std::cout << "Detected face: " << i << " -> (" << (float)face.center.x/320 << ", " << (float)face.center.y/240 << ")"<< std::endl;
                cv::ellipse(raspiCam->GetImageData(), cv::Point(face.center.x, face.center.y),
                            cv::Size(face.size.width / 2.0, face.size.height / 2.0), 0, 0, 360,
                            cv::Scalar(0, 0, 255), 4, 8, 0);
        }

        raspiCam->Save("./images/image(" + std::to_string(i) + ").jpg");
        std::cout << "Image #" << i << std::endl;
    }
>>>>>>> development

    std::cout << "\n\n\nCompleted: " << IMAGE_COUNT << " images\n\n\n"
              << std::endl;

    //Clean up
    delete raspiCam;
    delete faceAnalyzer;
    delete computerVision;

    return 0;
}
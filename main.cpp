#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

#pragma comment(lib, "opencv_world4100d") 

using namespace cv;
using namespace std;

void detectCircles(const std::string& imagePath) {
    Mat src = imread(imagePath, IMREAD_COLOR);
    if (src.empty()) {
        cerr << "file open error: " << imagePath << endl;
        return;
    }

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    GaussianBlur(gray, gray, Size(9, 9), 1.507, 1.505);

	// Hough Circle Transform
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 10, 142, 42.6, gray.rows / 11.8, gray.rows / 3.65);

    cout << "coins count: " << circles.size() << endl; 

    for (size_t i = 0; i < circles.size(); i++) {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        int radius = c[2];

        circle(src, center, 3, Scalar(0, 255, 0), -1, LINE_AA);
        circle(src, center, radius, Scalar(0, 0, 255), 3, LINE_AA);

        cout << "cirle " << i + 1 << ":centor(" << center.x << ", " << center.y << "), radius: " << radius << endl; // 
    }

    string outputFilename = imagePath + "_output.jpg";
    imwrite(outputFilename, src);

    imshow("Detected Circles", src);
    waitKey(0);
}


int main() {
    std::vector<std::string> imageFiles = {
        "coins0.jpg", "coins1.jpg", "coins2.jpg", "coins3.jpg", "coins4.jpg", "coins5.jpg"
    };
    for (const auto& imageFile : imageFiles) {
        cout << "image file: " << imageFile << endl;
        detectCircles(imageFile);
        cout << "--------------------------" << endl;
    }

    return 0;
}

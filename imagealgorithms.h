 #ifndef IMAGEALGORITHMS_H
 #define IMAGEALGORITHMS_H

// forward class declarations.
 class QImage;

 class ImageAlgorithms
 {
 public:
	// Helpers for editing.
    static void invertImage(QImage& thisImage);
    static void greyscale(QImage& thisImage);
    static void sepia(QImage& thisImage);
    static void edgeDetect(QImage& thisImage);
    static void rotateImage(QImage& thisImage, int delta);

    // Helpers for enhancing.
    static void changeBrightness(QImage &thisImage, int delta);
    static void changeSaturation(QImage &thisImage, int delta);
    static void filterImageFive(QImage &thisImage, double kernel[5][5], int kernelSize, int sumKernel);
    static void filterImageThree(QImage &thisImage, double kernel[3][3], int kernelSize, int sumKernel);
    static void changeContrast(QImage &thisImage, double delta);

    static QVector<int> findHistogram(QImage &thisImage);
 private:
    // Private data members.
	// NONE.
 };

 #endif

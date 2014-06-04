 #include <QtGui>
 #include <QtAlgorithms>

 #include "imagealgorithms.h"

 // Actions in the Edit menu.
 void ImageAlgorithms::invertImage(QImage& thisImage)
 {
     thisImage.invertPixels();
 }

 void ImageAlgorithms::greyscale(QImage& thisImage)
 {
     QColor oldColor;

     for(int x = 0; x < thisImage.width(); x++)
     {
         for(int y = 0; y < thisImage.height(); y++)
         {
             oldColor = QColor(thisImage.pixel(x,y));
             int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
             thisImage.setPixel(x,y,qRgb(average,average,average));
         }
     }
 }

 void ImageAlgorithms::sepia(QImage& thisImage)
 {
     QColor oldColor;
     int r, g, b;

     for(int x = 0; x < thisImage.width(); x++)
         {
             for(int y = 0; y < thisImage.height(); y++)
             {
                 oldColor = QColor(thisImage.pixel(x,y));
                 r = ((int)((oldColor.red()*0.393) + (oldColor.green()*0.769) + (oldColor.blue()*0.189)));
                 g = ((int)(oldColor.red()*0.349) + (oldColor.green()*0.686) + (oldColor.blue()*0.168));
                 b = ((int)(oldColor.red()*0.272) + (oldColor.green()*0.534) + (oldColor.blue()*0.131));

                 //we check if the new values are between 0 and 255
                 r = qBound(0, r, 255);
                 g = qBound(0, g, 255);
                 b = qBound(0, b, 255);

                 thisImage.setPixel(x,y, qRgb(r,g,b));
             }
         }
 }

 void ImageAlgorithms::edgeDetect(QImage& thisImage)
 {
     int kernelSize = 3;
     int sumKernel = 0;
     QColor colorData;
     QImage horizImage = thisImage;
     double kernelH [3][3]= {{-1, 0, 1},
                            {-2, 0, 2},
                            {-1, 0, 1}};
     filterImageThree(horizImage,kernelH,kernelSize,sumKernel);
     greyscale(horizImage);
     QImage vertImage = thisImage;
     double kernelV [3][3]= {{ 1, 2, 1},
                            { 0, 0, 0},
                            {-1,-2,-1}};
     filterImageThree(vertImage,kernelV,kernelSize,sumKernel);
     greyscale(vertImage);
     double horizComp = 0;
     double vertComp = 0;
     double outVal = 0;
     for(int x = 0; x < thisImage.width(); x++)
     {
         for(int y = 0; y < thisImage.height(); y++)
         {
             colorData = QColor(horizImage.pixel(x,y));
             horizComp = (double)colorData.red();
             colorData = QColor(vertImage.pixel(x,y));
             vertComp = (double)colorData.red();
             outVal = sqrt((horizComp*horizComp) + (vertComp*vertComp));
             if(outVal > 128)
                 outVal = 255;
             else
                 outVal = 0;
             thisImage.setPixel(x,y, qRgb((int)outVal,(int)outVal,(int)outVal));
         }
     }
 }

 void ImageAlgorithms::rotateImage(QImage& thisImage, int delta)
 {
     QTransform rotatebyAngle;
     rotatebyAngle.rotate(delta);
     thisImage = thisImage.transformed(rotatebyAngle);
 }

 // Actions in Enhance menu.

 // Helper for changing brightness.
 void ImageAlgorithms::changeBrightness(QImage& thisImage, int delta)
 {
     thisImage.convertToFormat(QImage::Format_ARGB32);
     QColor oldColor;
         int r,g,b;
         for(int x=0; x<thisImage.width(); x++)
         {
             for(int y=0; y<thisImage.height(); y++)
             {
                 oldColor = QColor(thisImage.pixel(x,y));

                 r = oldColor.red() + delta;
                 g = oldColor.green() + delta;
                 b = oldColor.blue() + delta;

                 //we check if the new values are between 0 and 255
                 r = qBound(0, r, 255);
                 g = qBound(0, g, 255);
                 b = qBound(0, b, 255);

                 thisImage.setPixel(x,y, qRgb(r,g,b));
             }
         }
 }

 // Helper for filtering an image with a 5 x 5 kernel
 void ImageAlgorithms::filterImageFive(QImage &thisImage, double kernel[][5], int kernelSize, int sumKernel)
 {
     double r,g,b;
     QColor color;

     for(int x = kernelSize/2; x < thisImage.width()-(kernelSize/2); x++)
     {
         for(int y = kernelSize/2; y < thisImage.height()-(kernelSize/2); y++)
         {
             r = 0;
             g = 0;
             b = 0;

             for(int i = -kernelSize/2; i <= kernelSize/2; i++){
                 for(int j = -kernelSize/2; j <= kernelSize/2; j++){
                     color = QColor(thisImage.pixel(x+i, y+j));
                     r += (double)color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                     g += (double)color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                     b += (double)color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                 }
             }
             if(sumKernel)
             {
                 r = qBound(0, (int)r/sumKernel, 255);
                 g = qBound(0, (int)g/sumKernel, 255);
                 b = qBound(0, (int)b/sumKernel, 255);
             }
             else
             {
                 r = qBound(0, (int)r, 255);
                 g = qBound(0, (int)g, 255);
                 b = qBound(0, (int)b, 255);
             }
             thisImage.setPixel(x,y,qRgb(r,g,b));
         }
     }
 }

  // Helper for filtering an image with a 3 x 3 kernel
 void ImageAlgorithms::filterImageThree(QImage &thisImage, double kernel[][3], int kernelSize, int sumKernel)
 {
     double r,g,b;
     QColor color;

     for(int x = kernelSize/2; x < thisImage.width()-(kernelSize/2); x++)
     {
         for(int y = kernelSize/2; y < thisImage.height()-(kernelSize/2); y++)
         {
             r = 0;
             g = 0;
             b = 0;

             for(int i = -kernelSize/2; i <= kernelSize/2; i++){
                 for(int j = -kernelSize/2; j <= kernelSize/2; j++){
                     color = QColor(thisImage.pixel(x+i, y+j));
                     r += (double)color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                     g += (double)color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                     b += (double)color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                 }
             }
             if(sumKernel)
             {
                 r = qBound(0, (int)r/sumKernel, 255);
                 g = qBound(0, (int)g/sumKernel, 255);
                 b = qBound(0, (int)b/sumKernel, 255);
             }
             else
             {
                 r = qBound(0, (int)r, 255);
                 g = qBound(0, (int)g, 255);
                 b = qBound(0, (int)b, 255);
             }
             thisImage.setPixel(x,y,qRgb(r,g,b));
         }
     }
 }

 // Helper for changing the Saturation of the image.
void ImageAlgorithms::changeSaturation(QImage &thisImage, int delta)
{
    QColor oldColor;
    QColor newColor;
    int h,s,l;

    for(int x=0; x < thisImage.width(); x++)
    {
        for(int y=0; y < thisImage.height(); y++)
        {
            oldColor = QColor(thisImage.pixel(x,y));

            newColor = oldColor.toHsl();
            h = newColor.hue();
            s = newColor.saturation()+delta;
            l = newColor.lightness();

            //we check if the new value is between 0 and 255
            s = qBound(0, s, 255);

            newColor.setHsl(h, s, l);

            thisImage.setPixel(x, y, qRgb(newColor.red(), newColor.green(), newColor.blue()));
        }
    }
}

void ImageAlgorithms::changeContrast(QImage &thisImage, double delta)
{
    QColor oldColor;
    int grayVal = 0;
    double factor = 0;

    // get histogram.
    QVector<int> table = findHistogram(thisImage);

    // find the first and last non-zero values.
    int minVal = 0;
    int maxVal = 255;
    int id = 0;
    while(table[id]==0)
        id++;
    minVal = id;
    id = maxVal;
    while(table[id]==0)
        id--;
    maxVal = id;

    if(maxVal != minVal)
    {
        double r,g,b;
        // do the linear scaling for contrast adjustment.
        for(int w=0; w < thisImage.width(); w++)
        {
            for(int h=0; h < thisImage.height(); h++)
            {
                oldColor = QColor(thisImage.pixel(w,h));
                grayVal = qGray(oldColor.red(),oldColor.green(),oldColor.blue());
                factor = (grayVal - minVal)*((double)(255 - 0)/(maxVal - minVal)) + 0;
                factor = (factor*delta)/grayVal;
                oldColor = QColor(thisImage.pixel(w,h));
                r = oldColor.red()*factor;
                g = oldColor.green()*factor;
                b = oldColor.blue()*factor;
                r = qBound(0, (int)r, 255);
                g = qBound(0, (int)g, 255);
                b = qBound(0, (int)b, 255);
                thisImage.setPixel(w, h, qRgb((int)r, (int)g, (int)b));
            }
        }
    }
}

QVector<int> ImageAlgorithms::findHistogram(QImage &thisImage)
{
    QColor oldColor;
    int grayVal;
    int colorCount = 256;
    QVector<int> table(colorCount);
    for(int idx = 0; idx < colorCount; idx++)
        table[idx] = 0;

    //convert to grayscale.
    for(int x = 0; x < thisImage.width(); x++)
    {
        for(int y = 0; y < thisImage.height(); y++)
        {
            oldColor = QColor(thisImage.pixel(x,y));
            grayVal = qGray(oldColor.red(),oldColor.green(),oldColor.blue());
            if(grayVal < 0)
                grayVal = 0;
            if(grayVal > colorCount-1)
                grayVal = colorCount-1;
            table[grayVal] = table[grayVal]+1;
        }
    }
    return table;
}

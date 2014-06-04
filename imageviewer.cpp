/****************************************************************************
 **
 ** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** You may use this file under the terms of the BSD license as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
 **     of its contributors may be used to endorse or promote products derived
 **     from this software without specific prior written permission.
 **
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

 #include <QtGui>
 #include <QtAlgorithms>

 #include "imageviewer.h"
 #include "imagealgorithms.h"

 //Constructor for the ImageViewer Class.
 ImageViewer::ImageViewer()
 {
     // QLabel is used for displaying text or an image.
     // No user interaction functionality is provided.
     imageLabel = new QLabel;
     imageLabel->setBackgroundRole(QPalette::Dark);
     imageLabel->setScaledContents(true);

     // QScrollArea provides a scrolling view around another widget.
     // If the child widget exceeds the size of the frame, QScrollArea
     // automatically provides scroll bars.
     scrollArea = new QScrollArea;
     scrollArea->setBackgroundRole(QPalette::Dark);
     scrollArea->setWidget(imageLabel);
     setCentralWidget(scrollArea);

     createActions();
     createMenus();
     createToolbar();
     createStatusBar();

     setWindowTitle(tr("Image Viewer"));
     // This is the initial size of the window.
     resize(500, 500);
 }

 // Helpers for the constructor.
 void ImageViewer::createActions()
 {
     // File menu actions.
     openAct = new QAction(tr("&Open..."), this);
     openAct->setShortcut(tr("Ctrl+O"));
     openAct->setIcon(QIcon(":/data/icons/Open.png"));
     connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

     printAct = new QAction(tr("&Print..."), this);
     printAct->setShortcut(tr("Ctrl+P"));
     printAct->setEnabled(false);
     connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

     saveAsAct = new QAction(tr("&Save As..."), this);
     saveAsAct->setShortcut(tr("Ctrl+S"));
     saveAsAct->setIcon(QIcon(":/data/icons/Save.png"));
     saveAsAct->setEnabled(false);
     connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

     exitAct = new QAction(tr("&Exit"), this);
     exitAct->setShortcut(tr("Ctrl+Q"));
     connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

     // Zoom menu actions.
     zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
     zoomInAct->setIcon(QIcon(":/data/icons/ZoomIn.png"));
     zoomInAct->setShortcut(tr("Ctrl++"));
     zoomInAct->setEnabled(false);
     connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

     zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
     zoomOutAct->setIcon(QIcon(":/data/icons/ZoomOut.png"));
     zoomOutAct->setShortcut(tr("Ctrl+-"));
     zoomOutAct->setEnabled(false);
     connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

     normalSizeAct = new QAction(tr("&Normal Size"), this);
     normalSizeAct->setShortcut(tr("Ctrl+S"));
     normalSizeAct->setEnabled(false);
     connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

     fitToWindowAct = new QAction(tr("&Fit to Window"), this);
     fitToWindowAct->setEnabled(false);
     fitToWindowAct->setCheckable(true);
     fitToWindowAct->setShortcut(tr("Ctrl+F"));
     connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

     // Edit menu actions.
     invertImageAct = new QAction(tr("&Invert Image"), this);
     invertImageAct->setShortcut(tr("Ctrl+I"));
     invertImageAct->setEnabled(false);
     connect(invertImageAct, SIGNAL(triggered()), this, SLOT(invertImage()));

     greyscaleAct = new QAction(tr("&Greyscale"), this);
     greyscaleAct->setShortcut(tr("Ctrl+G"));
     greyscaleAct->setEnabled(false);
     connect(greyscaleAct, SIGNAL(triggered()), this, SLOT(greyscale()));

     sepiaAct = new QAction(tr("&Sepia"), this);
     sepiaAct->setShortcut(tr("Ctrl+:"));
     sepiaAct->setEnabled(false);
     connect(sepiaAct, SIGNAL(triggered()), this, SLOT(sepia()));

     edgeDetectAct = new QAction(tr("&Edge Detect"), this);
     edgeDetectAct->setShortcut(tr("Ctrl+?"));
     edgeDetectAct->setEnabled(false);
     connect(edgeDetectAct, SIGNAL(triggered()), this, SLOT(edgeDetect()));


     rotateClockAct = new QAction(tr("&Rotate Clockwise"), this);
     rotateClockAct->setShortcut(tr("Ctrl+M"));
     rotateClockAct->setEnabled(false);
     connect(rotateClockAct, SIGNAL(triggered()), this, SLOT(rotateClock()));

     rotateCounterClockAct = new QAction(tr("&Rotate Counter Clockwise"), this);
     rotateCounterClockAct->setShortcut(tr("Ctrl+N"));
     rotateCounterClockAct->setEnabled(false);
     connect(rotateCounterClockAct, SIGNAL(triggered()), this, SLOT(rotateCounterClock()));

     // Enhance menu options.
     increaseBrightnessAct = new QAction(tr("&Increase Brightness"), this);
     increaseBrightnessAct->setShortcut(tr("Ctrl+U"));
     increaseBrightnessAct->setEnabled(false);
     connect(increaseBrightnessAct, SIGNAL(triggered()), this, SLOT(incBright()));

     decreaseBrightnessAct = new QAction(tr("&Decrease Brightness"), this);
     decreaseBrightnessAct->setShortcut(tr("Ctrl+J"));
     decreaseBrightnessAct->setEnabled(false);
     connect(decreaseBrightnessAct, SIGNAL(triggered()), this, SLOT(decBright()));

     sharpenAct = new QAction(tr("&Sharpen"), this);
     sharpenAct->setShortcut(tr("Ctrl+H"));
     sharpenAct->setEnabled(false);
     connect(sharpenAct, SIGNAL(triggered()), this, SLOT(sharpen()));

     blurAct = new QAction(tr("&Blur"), this);
     blurAct->setShortcut(tr("Ctrl+B"));
     blurAct->setEnabled(false);
     connect(blurAct, SIGNAL(triggered()), this, SLOT(blur()));

     increaseSaturationAct = new QAction(tr("&Increase Saturation"), this);
     increaseSaturationAct->setShortcut(tr("Ctrl+Q"));
     increaseSaturationAct->setEnabled(false);
     connect(increaseSaturationAct, SIGNAL(triggered()), this, SLOT(incSaturation()));

     decreaseSaturationAct = new QAction(tr("&Decrease Saturation"), this);
     decreaseSaturationAct->setShortcut(tr("Ctrl+A"));
     decreaseSaturationAct->setEnabled(false);
     connect(decreaseSaturationAct, SIGNAL(triggered()), this, SLOT(decSaturation()));

     increaseContrastAct = new QAction(tr("&Increase Contrast"), this);
     increaseContrastAct->setShortcut(tr("Ctrl+E"));
     increaseContrastAct->setEnabled(false);
     connect(increaseContrastAct, SIGNAL(triggered()), this, SLOT(incContrast()));

     decreaseContrastAct = new QAction(tr("&Decrease Contrast"), this);
     decreaseContrastAct->setShortcut(tr("Ctrl+F"));
     decreaseContrastAct->setEnabled(false);
     connect(decreaseContrastAct, SIGNAL(triggered()), this, SLOT(decContrast()));

     equalizeHistogramAct = new QAction(tr("&Equalize Histogram"), this);
     equalizeHistogramAct->setShortcut(tr("Ctrl+H"));
     equalizeHistogramAct->setIcon(QIcon(":/data/icons/Picture.png"));
     equalizeHistogramAct->setEnabled(false);
     connect(equalizeHistogramAct, SIGNAL(triggered()), this, SLOT(equalizeHistogram()));

     // Help menu actions.
     aboutAct = new QAction(tr("&About"), this);
     connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

     aboutQtAct = new QAction(tr("About &Qt"), this);
     connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
 }

 void ImageViewer::createMenus()
 {
     // called in the constructor.
     fileMenu = new QMenu(tr("&File"), this);
     fileMenu->addAction(openAct);
     fileMenu->addAction(printAct);
     fileMenu->addAction(saveAsAct);
     fileMenu->addSeparator();
     fileMenu->addAction(exitAct);

     viewMenu = new QMenu(tr("&View"), this);
     viewMenu->addAction(zoomInAct);
     viewMenu->addAction(zoomOutAct);
     viewMenu->addSeparator();
     viewMenu->addAction(normalSizeAct);
     viewMenu->addAction(fitToWindowAct);

     editMenu = new QMenu(tr("&Edit"), this);
     editMenu->addAction(invertImageAct);
     editMenu->addAction(greyscaleAct);
     editMenu->addAction(sepiaAct);
     editMenu->addAction(edgeDetectAct);
     editMenu->addSeparator();
     editMenu->addAction(rotateClockAct);
     editMenu->addAction(rotateCounterClockAct);

     enhanceMenu = new QMenu(tr("&Enhance"), this);
     enhanceMenu->addAction(increaseBrightnessAct);
     enhanceMenu->addAction(decreaseBrightnessAct);
     enhanceMenu->addSeparator();
     enhanceMenu->addAction(sharpenAct);
     enhanceMenu->addAction(blurAct);
     enhanceMenu->addSeparator();
     enhanceMenu->addAction(increaseSaturationAct);
     enhanceMenu->addAction(decreaseSaturationAct);
     enhanceMenu->addSeparator();
     enhanceMenu->addAction(increaseContrastAct);
     enhanceMenu->addAction(decreaseContrastAct);
     enhanceMenu->addSeparator();
     enhanceMenu->addAction(equalizeHistogramAct);

     helpMenu = new QMenu(tr("&Help"), this);
     helpMenu->addAction(aboutAct);
     helpMenu->addAction(aboutQtAct);

     // Do this after, because the Actions need to be added first.
     menuBar()->addMenu(fileMenu);
     menuBar()->addMenu(viewMenu);
     menuBar()->addMenu(editMenu);
     menuBar()->addMenu(enhanceMenu);
     menuBar()->addMenu(helpMenu);
 }

 void ImageViewer::createToolbar()
 {
     imToolbar = new QToolBar;
     imToolbar->setGeometry(0,0,200,20);

     imToolbar->addAction(openAct);
     imToolbar->addAction(saveAsAct);
     imToolbar->addAction(zoomInAct);
     imToolbar->addAction(zoomOutAct);
     imToolbar->addAction(equalizeHistogramAct);

     //don't allow moving the toolbar to other corners of the window.
     imToolbar->setMovable(0);
     imToolbar->setFloatable(0);
     addToolBar(Qt::TopToolBarArea, imToolbar);
 }

 void ImageViewer::createStatusBar()
 {
     statusBarNotification = new QLabel;
     statusBarNotification->setAlignment(Qt::AlignHCenter);
     statusBarNotification->setMinimumSize(statusBarNotification->sizeHint());
     statusBarNotification->setText("Ready...");

     statusBar()->addWidget(statusBarNotification);
 }

 // Actions in the file menu.
 void ImageViewer::open()
 {
     QString fileName = QFileDialog::getOpenFileName(this,
                                     tr("Open File"), QDir::currentPath());
     if (!fileName.isEmpty())
         {
         QImage image(fileName);
         if (image.isNull()) {
             QMessageBox::information(this, tr("Image Viewer"),
                                      tr("Cannot load %1.").arg(fileName));
             return;
         }
         imageLabel->setPixmap(QPixmap::fromImage(image));

         int imwidth = image.width();
         int imheight = image.height();
         // fix this
         resize(imwidth + 4, imheight + 80);
         setMaximumSize(imwidth + 4, imheight + 80);
         imageLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

         // enable printing once image is loaded.
         printAct->setEnabled(true);
         saveAsAct->setEnabled(true);
         // enable zoom actions.
         scaleFactor = 1.0;
         fitToWindowAct->setEnabled(true);
         updateZoomActions();

         if (fitToWindowAct->isChecked())
         {
             fitToWindow();
         }
         else
         {
             imageLabel->adjustSize();
         }
         // enable edit actions.
         invertImageAct->setEnabled(true);
         greyscaleAct->setEnabled(true);
         sepiaAct->setEnabled(true);
         edgeDetectAct->setEnabled(true);

         rotateClockAct->setEnabled(true);
         rotateCounterClockAct->setEnabled(true);

         // enable enhance actions.
         increaseBrightnessAct->setEnabled(true);
         decreaseBrightnessAct->setEnabled(true);

         sharpenAct->setEnabled(true);
         blurAct->setEnabled(true);

         increaseSaturationAct->setEnabled(true);
         decreaseSaturationAct->setEnabled(true);

         increaseContrastAct->setEnabled(true);
         decreaseContrastAct->setEnabled(true);

         equalizeHistogramAct->setEnabled(true);

         // Update the status bar with image size.
         QString statusShow = "Image Size: ("+QString::number(imwidth)+", "+QString::number(imheight)+")";
         //statusBar()->showMessage(statusShow);
         statusBarNotification->setText(statusShow);
     }
 }

 void ImageViewer::print()
 {
     Q_ASSERT(imageLabel->pixmap());
 #ifndef QT_NO_PRINTER
     QPrintDialog dialog(&printer, this);
     if (dialog.exec())
     {
         QPainter painter(&printer);
         QRect rect = painter.viewport();
         QSize size = imageLabel->pixmap()->size();
         size.scale(rect.size(), Qt::KeepAspectRatio);
         painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
         painter.setWindow(imageLabel->pixmap()->rect());
         painter.drawPixmap(0, 0, *imageLabel->pixmap());
     }
 #endif
 }

 void ImageViewer::saveAs()
 {
     Q_ASSERT(imageLabel->pixmap());
     QString filename = QFileDialog::getSaveFileName(this,
             tr("Save File"),
             QDir::currentPath(),
             "Images (*.png *.bmp *.jpg *.tif);");
     QImage thisImage = imageLabel->pixmap()->toImage();
     if (!thisImage.save(filename))
     {
         QMessageBox::information(this, tr("Image Viewer"),
                                  tr("Did not save file."));
         return;
     }
 }

 // Actions in the Zoom menu.
 void ImageViewer::zoomIn()
 {
     scaleImage(1.25);
 }

 void ImageViewer::zoomOut()
 {
     scaleImage(0.8);
 }

 void ImageViewer::normalSize()
 {
     imageLabel->adjustSize();
     scaleFactor = 1.0;
 }

 void ImageViewer::fitToWindow()
 {
     bool fitToWindow = fitToWindowAct->isChecked();
     scrollArea->setWidgetResizable(fitToWindow);
     if (!fitToWindow)
     {
         normalSize();
     }
     else
     {
         imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     }
     updateZoomActions();
 }

 // Helper for zoom actions.
 void ImageViewer::scaleImage(double factor)
 {
     Q_ASSERT(imageLabel->pixmap());
     scaleFactor *= factor;
     imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

     adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
     adjustScrollBar(scrollArea->verticalScrollBar(), factor);

     zoomInAct->setEnabled(scaleFactor < 3.0);
     zoomOutAct->setEnabled(scaleFactor > 0.333);
 }

 void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
 {
     scrollBar->setValue(int(factor * scrollBar->value()
                             + ((factor - 1) * scrollBar->pageStep()/2)));
 }

 void ImageViewer::updateZoomActions()
 {
     zoomInAct->setEnabled(!fitToWindowAct->isChecked());
     zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
     normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
 }

 // Actions in the Edit menu.
 void ImageViewer::invertImage()
 {
     Q_ASSERT(imageLabel->pixmap());
     QImage thisImage = imageLabel->pixmap()->toImage();
     ImageAlgorithms::invertImage(thisImage);
     QPixmap mypixmap = QPixmap::fromImage(thisImage);
     imageLabel->setPixmap(mypixmap);
 }

 void ImageViewer::greyscale()
 {
     Q_ASSERT(imageLabel->pixmap());
     QImage thisImage = imageLabel->pixmap()->toImage();
     ImageAlgorithms::greyscale(thisImage);
     QPixmap mypixmap = QPixmap::fromImage(thisImage);
     imageLabel->setPixmap(mypixmap);
 }

 void ImageViewer::sepia()
 {
     Q_ASSERT(imageLabel->pixmap());
     QImage thisImage = imageLabel->pixmap()->toImage();
     ImageAlgorithms::sepia(thisImage);
     QPixmap mypixmap = QPixmap::fromImage(thisImage);
     imageLabel->setPixmap(mypixmap);
 }

 void ImageViewer::edgeDetect()
 {
     Q_ASSERT(imageLabel->pixmap());
     QImage thisImage = imageLabel->pixmap()->toImage();
     ImageAlgorithms::edgeDetect(thisImage);
     QPixmap mypixmap = QPixmap::fromImage(thisImage);
     imageLabel->setPixmap(mypixmap);
 }

 void ImageViewer::rotateClock()
 {
     Q_ASSERT(imageLabel->pixmap());
     QImage thisImage = imageLabel->pixmap()->toImage();
     ImageAlgorithms::rotateImage(thisImage, 90);
     QPixmap mypixmap = QPixmap::fromImage(thisImage);
     imageLabel->setPixmap(mypixmap);
 }

 void ImageViewer::rotateCounterClock()
 {
     Q_ASSERT(imageLabel->pixmap());
     QImage thisImage = imageLabel->pixmap()->toImage();
     ImageAlgorithms::rotateImage(thisImage, -90);
     QPixmap mypixmap = QPixmap::fromImage(thisImage);
     imageLabel->setPixmap(mypixmap);
 }

 // Actions in Enhance menu.

 void ImageViewer::incBright()
 {
     Q_ASSERT(imageLabel->pixmap());
     QImage thisImage = imageLabel->pixmap()->toImage();
     ImageAlgorithms::changeBrightness(thisImage, 5);
     QPixmap mypixmap = QPixmap::fromImage(thisImage);
     imageLabel->setPixmap(mypixmap);
 }

 void ImageViewer::decBright()
 {
     Q_ASSERT(imageLabel->pixmap());
     QImage thisImage = imageLabel->pixmap()->toImage();
     ImageAlgorithms::changeBrightness(thisImage, -5);
     QPixmap mypixmap = QPixmap::fromImage(thisImage);
     imageLabel->setPixmap(mypixmap);
 }

 void ImageViewer::sharpen()
 {
     Q_ASSERT(imageLabel->pixmap());
     QImage thisImage = imageLabel->pixmap()->toImage();
     double kernel [3][3]= {{0,-1, 0},
                            {-1, 5,-1},
                            {0,-1, 0}};
     /*
     {{0.0448,    0.0468,    0.0564,    0.0468,    0.0448},
     {0.0468,    0.3167,    0.7146,    0.3167,    0.0468},
     {0.0564,    0.7146,   -4.9048,    0.7146,    0.0564},
     {0.0468,    0.3167,    0.7146,    0.3167,    0.0468},
     {0.0448,    0.0468,    0.0564,    0.0468,    0.0448}}
     */
     int kernelSize = 3;
     int sumKernel = 1;
     ImageAlgorithms::filterImageThree(thisImage,kernel,kernelSize,sumKernel);
     QPixmap mypixmap = QPixmap::fromImage(thisImage);
     imageLabel->setPixmap(mypixmap);
 }

 void ImageViewer::blur()
 {
     Q_ASSERT(imageLabel->pixmap());
     QImage thisImage = imageLabel->pixmap()->toImage();
     double kernel [5][5]= {{0,0,1,0,0},
                         {0,1,3,1,0},
                         {1,3,7,3,1},
                         {0,1,3,1,0},
                         {0,0,1,0,0}};
     int kernelSize = 5;
     int sumKernel = 27;
     ImageAlgorithms::filterImageFive(thisImage,kernel,kernelSize,sumKernel);
     QPixmap mypixmap = QPixmap::fromImage(thisImage);
     imageLabel->setPixmap(mypixmap);
 }

 void ImageViewer::incSaturation()
 {
     Q_ASSERT(imageLabel->pixmap());
     QImage thisImage = imageLabel->pixmap()->toImage();
     ImageAlgorithms::changeSaturation(thisImage, 5);
     QPixmap mypixmap = QPixmap::fromImage(thisImage);
     imageLabel->setPixmap(mypixmap);
 }

 void ImageViewer::decSaturation()
 {
     Q_ASSERT(imageLabel->pixmap());
     QImage thisImage = imageLabel->pixmap()->toImage();
     ImageAlgorithms::changeSaturation(thisImage, -5);
     QPixmap mypixmap = QPixmap::fromImage(thisImage);
     imageLabel->setPixmap(mypixmap);
 }

void ImageViewer::incContrast()
{
    Q_ASSERT(imageLabel->pixmap());
    QImage thisImage = imageLabel->pixmap()->toImage();
    ImageAlgorithms::changeContrast(thisImage, 1.2);
    QPixmap mypixmap = QPixmap::fromImage(thisImage);
    imageLabel->setPixmap(mypixmap);
}

void ImageViewer::decContrast()
{
    Q_ASSERT(imageLabel->pixmap());
    QImage thisImage = imageLabel->pixmap()->toImage();
    ImageAlgorithms::changeContrast(thisImage, 0.5);
    QPixmap mypixmap = QPixmap::fromImage(thisImage);
    imageLabel->setPixmap(mypixmap);
}

void ImageViewer::equalizeHistogram()
{
    Q_ASSERT(imageLabel->pixmap());
    QImage thisImage = imageLabel->pixmap()->toImage();
    ImageAlgorithms::changeContrast(thisImage, 1);
    QPixmap mypixmap = QPixmap::fromImage(thisImage);
    imageLabel->setPixmap(mypixmap);
}

 // Actions in the Help menu.
 void ImageViewer::about()
 {
     QMessageBox::about(this, tr("About Image Viewer"),
             tr("<p>The <b>Image Viewer</b> uses QT 4.8 and includes several image manipulation features. "
                "This is an extended version of the online example,"
                "available at <a>http://qt-project.org/doc/qt-4.8/widgets-imageviewer.html</a>"
                "</p>"));
 }

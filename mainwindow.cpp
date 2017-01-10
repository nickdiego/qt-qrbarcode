#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>
#include <cstdio>
#include <cstdlib>

#include <QtCore/QTimer>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QWidget>

#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include <opencv2/legacy/legacy.hpp>

#include "zbar.h"
#include "zbar/Image.h"
#include "zbar/ImageScanner.h"
#include "zbar/Video.h"

#include "zint.h"


using namespace zbar;
using namespace cv;

typedef struct parameter Parameter;
struct parameter {
  float alpha;
  float beta;
  float gamma;
};

int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
Mat src_gray;

struct zint_symbol *my_symbol;

QString strFilePath;
CvCapture* capture;
QTimer *timer;
int symbology=1;
void thresh_callback(int, void* );

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addListSymbology();

    on_radioText_clicked();
}
void MainWindow::addListSymbology()
{

    ui->cbListCode->removeItem(0);
    ui->cbListCode->addItem("Standard Code 2 of 5");    //2
    ui->cbListCode->addItem("Interleaved 2 of 5");      //3
    ui->cbListCode->addItem("Code 3 of 9 (Code 39)");   //8
    ui->cbListCode->addItem("Extended Code 3 of 9 (Code 39+)"); //9
    ui->cbListCode->addItem("EAN");
    ui->cbListCode->addItem("UPC A");
    ui->cbListCode->addItem("UPC E");
    ui->cbListCode->addItem("PDF417");
    ui->cbListCode->addItem("Code 128");
    ui->cbListCode->addItem("QRCODE");
}

MainWindow::~MainWindow()
{
    // Release the capture device housekeeping
    cvReleaseCapture( &capture );
    delete ui;

}

void MainWindow::on_ImageButton_clicked()
{
    cvReleaseCapture;
    int n;
    //Tim den file anh can giai ma
    strFilePath = QFileDialog::getOpenFileName(this, tr("Open a image"), QDir::currentPath(), tr("Image Files (*.jpg *.jpeg *.png)"));
    if(strFilePath.size())
    {

       IplImage *src = cvLoadImage((const char*)strFilePath.toLatin1().data(),CV_LOAD_IMAGE_COLOR);

        // Create a QImage to show the captured images
        QImage img_show = QImage((const unsigned char*)(src->imageData),src->width,src->height,QImage::Format_RGB888).rgbSwapped();
        ui->showlabel->setPixmap(QPixmap::fromImage(img_show,Qt::AutoColor).scaledToWidth(300));
        n=ScanImage(src);
        //if(n>0)
        {
          //  cvReleaseCapture(&capture);
        }
    }
}
void MainWindow::on_VideoButton_clicked()
{

    strFilePath = QFileDialog::getOpenFileName(this, tr("Open a video"), QDir::currentPath(), tr("Video Files (*.mp4 *.flv *.wmv)"));
    capture=cvCaptureFromFile(strFilePath.toLatin1().data());
    if(capture)
    {
        timer = new QTimer(this);
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(ProcessFrame()));

        timer->start(1000/30);
    }
    else ui->textResult->setText("Cannot connect to Camera!");
 }

void MainWindow::on_CameraButton_clicked()
{
    //Kiem tra trang thai bat tat cua camera
    if(capture == 0)
    {
        capture = cvCaptureFromCAM(CV_CAP_ANY);
        if(capture)
        {
            cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT,1600);
            cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH,1600);

            timer = new QTimer(this);

            QObject::connect(timer,SIGNAL(timeout()),this,SLOT(ProcessFrame()));

            timer->start(1000/30);
        }
        else ui->textResult->setText("Cannot connect to Camera!");
    }

    return ;
}

int MainWindow::ScanImage(IplImage *src)
{

    IplImage *img = cvCreateImage(cvSize(src->width,src->height), IPL_DEPTH_8U,1);

    cvCvtColor( src, img, CV_RGB2GRAY );

    //Su dung thu vien Zbar de giai ma

    uchar* raw = (uchar *)img->imageData;
    int width = img->width;
    int height = img->height;

    ImageScanner *scanner=new ImageScanner();

    scanner->set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    Image *zimg = new Image(width,height,"Y800",raw,width*height);

    int n=scanner->scan(*zimg);

    if(n>0)
    {
        for(Image::SymbolIterator symbol = zimg->symbol_begin(); symbol != zimg->symbol_end(); ++symbol)
        {
            //Hien thi ket qua len Textbox
            ui->textResult->setPlainText(QString::fromStdString(symbol->get_data()));
        }

    }

    else
    {
        ui->textResult->setPlainText("Cannot Detect Code!");
    }

    //Giai phong tai nguyen
    zimg->set_data(NULL, 0);

    return n;
}

void MainWindow::ProcessFrame()
{
    IplImage* src = cvQueryFrame(capture);
    QImage img_show = QImage((unsigned char*)(src->imageData), src->width,
                             src->height, QImage::Format_RGB888).rgbSwapped();
    ui->showlabel->setPixmap(QPixmap::fromImage(img_show,Qt::AutoColor).scaledToWidth(300));

    int n = ScanImage(src);

    if(n)
    {
        timer->stop();
        cvReleaseCapture(&capture);
    }
}

//////////////////////////////////////////////////////
//Encoder text -> Image;
void MainWindow::createEncode()
{
    QString content="";
    my_symbol = ZBarcode_Create();
    my_symbol->border_width=10;
    my_symbol->symbology=symbology;
     //my_symbol->scale=5.0;
    if(my_symbol != NULL)
    {
        content = ui->textBarcode->toPlainText();
        unsigned char * sequence=NULL;
        sequence=(unsigned char*)qstrdup(content.toLatin1().constData());

        //strcpy(my_symbol->outfile,(char*)qstrdup(content.toLatin1().constData()));

        ZBarcode_Encode_and_Print(my_symbol,sequence,0,0);
    }
    ZBarcode_Delete(my_symbol);

    showImageEncode();
}
void MainWindow::createEncodeQR()
{
    QString content="";
    my_symbol = ZBarcode_Create();
    my_symbol->border_width=10;
    my_symbol->symbology=symbology;
     my_symbol->scale=5.0;
    if(my_symbol != NULL)
    {
        content = ui->textResult_2->toPlainText()+" "+ui->textResult_3->toPlainText()+" "+ui->textResult_4->toPlainText();
        unsigned char * sequence=NULL;
        sequence=(unsigned char*)qstrdup(content.toLatin1().constData());

        //strcpy(my_symbol->outfile,(char*)qstrdup(content.toLatin1().constData()));

        ZBarcode_Encode_and_Print(my_symbol,sequence,0,0);
    }
    ZBarcode_Delete(my_symbol);

    showImageEncode();
}

void MainWindow::on_btEncode_clicked()
{
    if(symbology!=58)
    {
        createEncode();
    }
    else
    {
        createEncodeQR();
    }

}


void MainWindow::showImageEncode()
{
    QString path = QDir::currentPath()+"/out.png";

    IplImage *src = cvLoadImage((const char*)path.toLatin1().data(),CV_LOAD_IMAGE_COLOR);

     QImage img_show = QImage((const unsigned char*)(src->imageData),src->width,src->height,QImage::Format_RGB888).rgbSwapped();
     ui->showlabel_2->setPixmap(QPixmap::fromImage(img_show,Qt::AutoColor).scaledToWidth(185));
}

void MainWindow::readFromFileText()
{
    struct zint_symbol * barcode;
    barcode=ZBarcode_Create();
    strFilePath=QFileDialog::getOpenFileName(this,tr("Open file text"),QDir::currentPath(),tr("Text file(*.txt)"));
    char * sequence=NULL;
    sequence=(char*)qstrdup(strFilePath.toLatin1().constData());
    if(barcode!=NULL)
    {
        ZBarcode_Encode_File_and_Print(barcode,sequence,0);
       // ZBarcode_Encode(barcode,sequence,10);
    }
    ZBarcode_Delete(barcode);
}

void MainWindow::on_pushButton_clicked()
{
    readFromFileText();
    showImageEncode();
}

void MainWindow::disableBarcode()
{
    ui->textBarcode->show();
    ui->groupQr1->hide();
    ui->groupQr2->setTitle("Input barcode:");
    ui->label_content->hide();
}
void MainWindow::enableQRcode()
{
    ui->groupQr1->show();
    ui->groupQr2->setTitle("Content:");
    ui->label_content->show();
    ui->textBarcode->hide();
}
void MainWindow::on_cbListCode_currentIndexChanged()
{
    switch (ui->cbListCode->currentIndex())
    {
    case 0: {symbology=2;disableBarcode();break;}
    case 1: {symbology=3;disableBarcode();break;}
        case 2: symbology=8;disableBarcode();break;
        case 3: symbology=9;disableBarcode();break;
        case 4: symbology=13;disableBarcode();break;
        case 5: symbology=34;disableBarcode();break;
        case 6: symbology=37;disableBarcode();break;
        case 7: symbology=55;disableBarcode();break;
        case 8: symbology=60;disableBarcode();break;
        case 9:
        {
            symbology=58;
            enableQRcode();
            break;
        }
    }
}

void MainWindow::on_btnSave_clicked()
{
    strFilePath = QFileDialog::getOpenFileName(this, tr("Open a video"), QDir::currentPath(), tr("Video Files (*.mp4 *.flv *.wmv)"));
    capture=cvCaptureFromFile(strFilePath.toLatin1().data());
    if(capture)
    {
        timer = new QTimer(this);
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT( use_drawRectangle()));

        timer->start(1000/30);
    }
    else ui->textResult->setText("Cannot connect to Camera!");

}

void MainWindow::on_pushButton_2_clicked()
{
    strFilePath = QFileDialog::getOpenFileName(this, tr("Open a image"), QDir::currentPath(), tr("Image Files (*.jpg *.jpeg *.png)"));

    if(strFilePath.size())
    {
        cv::Mat test;

        char * sequence=NULL;
        sequence=(char*)qstrdup(strFilePath.toLatin1().constData());
        test=cv::imread(sequence);
        //test=cv::imread(strFilePath);

        /// Convert it to gray,blue
        cvtColor( test, src_gray, CV_BGR2GRAY );
        blur(src_gray,src_gray,Size(1,1));
        /// Create Window
        char* source_window = "Source";
        namedWindow( source_window, CV_WINDOW_NORMAL );
        imshow( source_window, test );
        createTrackbar( " Threshold:", "Source", &thresh, max_thresh,thresh_callback);
        thresh_callback( 0, 0);

    }
}
void thresh_callback(int, void*)
{

    //Mat src_copy = src.clone();
    Mat threshold_output;
    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    /// Detect edges using Threshold
    threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    /// Find the convex hull object for each contour
    std::vector<std::vector<Point> >hull( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
    { convexHull( Mat(contours[i]), hull[i], false ); }
    /// Draw contours + hull results
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    drawContours( drawing, contours, i, color, 1, 8, std::vector<Vec4i>(), 0, Point() );
    drawContours( drawing, hull, i, color, 1, 8, std::vector<Vec4i>(), 0, Point() );
    }
    /// Show in a window
    namedWindow( "Hull demo", CV_WINDOW_NORMAL);
    imshow( "Hull demo", drawing );

}

void MainWindow::use_drawRectangle()
{
        IplImage *src_img = 0, *dst_img;
      IplImage *src_img_gray = 0;
      IplImage *tmp_img;
      CvMemStorage *storage = cvCreateMemStorage (0);
      CvSeq *contours = 0;
      CvBox2D ellipse;
      CvTreeNodeIterator it;
      CvPoint2D32f pt[4];

      IplImage* src = cvQueryFrame(capture);


      src_img=src;

      src_img_gray = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
      cvCvtColor (src_img, src_img_gray, CV_BGR2GRAY);
      tmp_img = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
      dst_img = cvCloneImage (src_img);

      cvThreshold (src_img_gray, tmp_img, 100, 255, CV_THRESH_BINARY);
      cvFindContours (tmp_img, storage, &contours, sizeof (CvContour),
                      CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint (0, 0));

      cvInitTreeNodeIterator (&it, contours, 3);

      while ((contours = (CvSeq *) cvNextTreeNode (&it)) != NULL)
      {
        if (contours->total > 5) {

          ellipse = cvFitEllipse2 (contours);
          ellipse.angle = 90.0 - ellipse.angle;

          cvDrawContours (dst_img, contours, CV_RGB (255, 0, 0), CV_RGB (255, 0, 0), 0, 1, CV_AA, cvPoint (0, 0));
          //cvEllipseBox (dst_img, ellipse, CV_RGB (0, 0, 255), 2);
          //cvBoxPoints (ellipse, pt);
          cvLine (dst_img, cvPointFrom32f (pt[0]), cvPointFrom32f (pt[1]), CV_RGB (0, 255, 0));
          cvLine (dst_img, cvPointFrom32f (pt[1]), cvPointFrom32f (pt[2]), CV_RGB (0, 255, 0));
          cvLine (dst_img, cvPointFrom32f (pt[2]), cvPointFrom32f (pt[3]), CV_RGB (0, 255, 0));
          cvLine (dst_img, cvPointFrom32f (pt[3]), cvPointFrom32f (pt[0]), CV_RGB (0, 255, 0));
        }

      }

      //cvNamedWindow ("Fitting", CV_WINDOW_NORMAL);
      //cvShowImage ("Fitting", dst_img);

      QImage img_show = QImage((unsigned char*)(dst_img->imageData),dst_img->width,dst_img->height,QImage::Format_RGB888).rgbSwapped();
      ui->showlabel->setPixmap(QPixmap::fromImage(img_show,Qt::AutoColor).scaledToWidth(300));
      int n = ScanImage(dst_img);

      if(n)
      {
          timer->stop();
          cvReleaseCapture(&capture);
      }

      /*

      cvWaitKey (0);
      cvDestroyWindow ("Fitting");
      cvReleaseImage (&src_img);
      cvReleaseImage (&dst_img);
      cvReleaseImage (&src_img_gray);
      cvReleaseImage (&tmp_img);*/
      cvReleaseMemStorage (&storage);


}
void MainWindow::snake()
{


}
void MainWindow::on_pushButton_3_clicked()
{
    strFilePath = QFileDialog::getOpenFileName(this, tr("Open a video"), QDir::currentPath(), tr("Video Files (*.mp4 *.flv *.wmv)"));
    capture=cvCaptureFromFile(strFilePath.toLatin1().data());
    if(capture)
    {
        timer = new QTimer(this);
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(snake()));

        timer->start(1000/30);
    }
    else ui->textResult->setText("Cannot connect to Camera!");
}

void MainWindow::on_radioURL_clicked()
{
    ui->label_content->setText("URL:");
    ui->textResult_2->setText("http://");
    ui->textResult_2->resize(341,30);
    ui->textResult_3->hide();
    ui->label_content_2->hide();
    ui->label_content_3->hide();
    ui->textResult_4->hide();
}

void MainWindow::on_radioText_clicked()
{

    ui->textResult_2->setText("");
    ui->label_content->setText("Text:\t\t\t (250 Character left)");
    ui->textResult_2->resize(341,100);
    ui->textResult_3->hide();
    ui->label_content_2->hide();
    ui->label_content_3->hide();
    ui->textResult_4->hide();
}

void MainWindow::on_radioDial_clicked()
{
    ui->textResult_2->setText("");
    ui->label_content->setText("Dial:");
    ui->textResult_2->resize(341,30);
    ui->textResult_3->hide();
    ui->label_content_2->hide();
    ui->label_content_3->hide();
    ui->textResult_4->hide();

}

void MainWindow::on_radioSMS_clicked()
{
    ui->label_content->setText("Dial:");
    ui->textResult_2->setText("");
    ui->textResult_2->resize(341,30);
    ui->textResult_3->show();
    ui->label_content_2->show();
    ui->label_content_2->setText("Message:");
    ui->textResult_3->resize(341,60);
    ui->label_content_3->hide();
    ui->textResult_4->hide();
}

void MainWindow::on_radioContact_clicked()
{
    ui->label_content->setText("Name:");
    ui->textResult_2->setText("");
    ui->textResult_2->resize(341,30);
    ui->textResult_3->show();
    ui->label_content_2->show();
    ui->label_content_2->setText("Tel:");
    ui->textResult_3->resize(341,30);
    ui->label_content_3->show();
    ui->label_content_3->setText("Email:");
    ui->textResult_4->show();
    ui->textResult_4->resize(341,30);
}
void MainWindow::clearAll()
{
    ui->textResult_2->setText("");
    ui->textResult_3->setText("");
    ui->textResult_4->setText("");
}

void MainWindow::on_btEncode_2_clicked()
{
    //QMessageBox::information(this,"", QFileDialog::getSaveFileName(this,tr("Save File"),QDir::currentPath(),tr("Files Format (*.png)")));
     strFilePath = QFileDialog::getSaveFileName(this,tr("Save File"),QDir::currentPath(),tr("PNG (*.png)"));
     char *m="agfdsaf";
    strcpy(strFilePath.toLatin1().data() ,m);
}

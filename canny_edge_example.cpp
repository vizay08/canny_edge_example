#include <opencv2\opencv.hpp>
bool leftbuttondown = false;
void my_mouse_callback(int event,int x,int y,int flags ,void *param);
void mouseCall(int event,int x ,int y,int flags,void *img);

cv::Mat selectedImage,selectedGrayImage,selectedBlurImage,edges;
int xstart=-1,xend=-1;
int ystart=-1,yend=-1;
int xmove=-1,ymove=-1;  //mouse motion coordinates
int *xm,*ym;  //pointer for motion coordinates
long c=0;   //counter for pointer motion


int main()
{
	char t;
	char *s = (char *)malloc(sizeof(char)*20);
	gets(s);
	cv::Mat image = cv::imread(s);
	
	cv::namedWindow("image");
	
	cv::cvtColor(image,selectedGrayImage,CV_RGB2GRAY);
			cv::imshow("slected gray image",selectedGrayImage);
			//selectedBlurImage = cv::Mat(image.rows,image.cols,selectedGrayImage.type());
			cv::GaussianBlur( selectedGrayImage, selectedBlurImage, cv::Size(7,7), 1.5, 1.5);
			cv::imshow("slected blur image",selectedBlurImage);
			cv::Canny(selectedBlurImage,edges,0,30,3);
		
			cv::imshow("canny edge detection",edges);
	
	cv::setMouseCallback("image",my_mouse_callback,&image);
	
	
		while(cv::waitKey(15)!='a')
		{
			
			if(xstart!=-1&& ystart!=-1&&xend!=-1&&yend!=-1){
				cv:: rectangle(image,cv::Rect (cv::Point(xstart,ystart),cv::Point(xend,yend)),cv::Scalar(255,0,0));
				selectedImage = cv::Mat(image,cv::Rect (cv::Point(xstart,ystart),cv::Point(xend,yend)));
				cv::imshow("selected image",selectedImage);

				cv::cvtColor(selectedImage,selectedGrayImage,CV_RGB2GRAY);
			cv::imshow("slected gray image",selectedGrayImage);
			//selectedBlurImage = cv::Mat(image.rows,image.cols,selectedGrayImage.type());
			cv::GaussianBlur( selectedGrayImage, selectedBlurImage, cv::Size(3,3), 1.5, 1.5);
			cv::imshow("slected blur image",selectedBlurImage);
			cv::Canny(selectedBlurImage,edges,0,30,3);
		
			cv::imshow("canny edge detection",edges);
			xstart =-1,ystart =-1,xend  = -1 ,yend =-1;
			}

				
			cv::imshow("image",image);
		}
		/*
			cv::cvtColor(selectedImage,selectedGrayImage,CV_RGB2GRAY);
			cv::imshow("slected gray image",selectedGrayImage);
			cv::blur(selectedGrayImage,selectedBlurImage,selectedGrayImage.size());
			cv::imshow("slected blur image",selectedBlurImage);
			cv::Canny(selectedBlurImage,edges,0,30,3);
		
			cv::imshow("canny edge detection",edges);
		*/cv::waitKey();
		
	
  	return 0;
	
}

void my_mouse_callback( int event, int x, int y, int flags, void* param ){
//IplImage* image = (IplImage*) param;

	
	cv::Mat &img=(*(cv::Mat *)param);
	//cv::Mat image = images[0];
	

	

switch( event ){

	
	case CV_EVENT_LBUTTONDOWN : 
		leftbuttondown = true;
		xstart=x;
		ystart=y;
		printf("LEft button down %d %d\n",x,y);
		break;


	case CV_EVENT_LBUTTONUP:
		leftbuttondown = false;
		cv::imshow("butup",img);
		xend=x;
		yend=y;
		break;

/*	case CV_EVENT_MOUSEMOVE:
		if(leftbuttondown)
		{
				cv::Point point = cv::Point(x,y);
			
		
			c++;
			printf("MOUSE MOVe %d %d %ld\n",x,y,c);
		}	
		break;*/
    case CV_EVENT_RBUTTONDOWN:
        printf("RBUTTONDOWN\n");

        break;

    case CV_EVENT_FLAG_CTRLKEY:
        printf("FLAG_LBUTTONDBLCLK\n");
        break;

		


cv::waitKey(1);
}

}

void mouseCall(int event,int x ,int y,int flags,void *img)//updates the mouse motion co-ordinates.....
{
	xmove = x;
	ymove = y ;
}


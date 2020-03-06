void callback(const sensor_msgs::Image::ConstPtr &msg)
{

    if (check_moving_obs)
    {
        if (img_previous.data.size() == 0)
        {
            img_previous = *msg;
            img_primary = *msg;
        }
        else
        {
            img_previous = img_current;
        }
        img_current = *msg;

        cout << "------------------------header of msg :---------:" << msg->header.seq << "\n";
        cout << "------------------------current image info :---------:" << img_current.data.size() << "\n";
        cout << "------------------------Height :---------:" << img_current.height << "\n";
        cout << "------------------------Width :---------:" << img_current.width << "\n";

        cout << "------------------------previous image info :---------:" << img_previous.data.size() << "\n";
        cout << "------------------------Height :---------:" << img_previous.height << "\n";
        cout << "------------------------Width :---------:" << img_previous.width << "\n";

        //Convert from the ROS image message to a CvImage suitable for working with OpenCV for processing
        cv_bridge::CvImagePtr cv_ptr_prev, cv_ptr_cur;
        cv::Mat image_cur, image_pre, differenceImage;
        //thresholded difference image (for use in findContours() function)
        cv::Mat thresholdImage;

        try
        {

            //Always copy, returning a mutable CvImage
            //OpenCV expects color images to use BGR channel order.
            cv_ptr_cur = cv_bridge::toCvCopy(msg, enc::TYPE_32FC1);           //cv_bridge::toCvCopy(img_current, enc::BGR8);
            cv_ptr_prev = cv_bridge::toCvCopy(img_previous, enc::TYPE_32FC1); //TYPE_16UC1

            image_cur = cv_ptr_cur->image;
            image_pre = cv_ptr_prev->image;
            int count_diff = 0;
            bool motion_detected = false;

            //perform frame differencing with the sequential images.
            cv::absdiff(image_cur, image_pre, differenceImage);
            //threshold intensity image at a given sensitivity value
            cv::threshold(differenceImage, thresholdImage, 20, 255, cv::THRESH_BINARY);
            cout << "~~~~~~~~~~~~IMP~~~~~~~~~~difference image info :---------:" << thresholdImage.rows << "\n";
            cout << "~~~~~~~~~~~~~IMP~~~~~~~~~difference image info :---------:" << thresholdImage.cols << "\n";
            for (int j = 0; j < thresholdImage.rows; ++j)
            {
                //const double* Mi = differenceImage.ptr<double>(j);
                for (int i = 0; i < thresholdImage.rows; ++i)
                {
                    //cout<<"diff img pixel val : "<<Mi[i]<<"\n";
                    //double depth = thresholdImage.at<double>(cv::Point(j,i));
                    //cout<<"diff img depth val : "<<depth<<"\n";
                    cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
                    cout << "+++++ i: " << i << "------ j : " << j << "++++++++++++++++++++++++++++++++++++++++\n";
                    cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
                    cout << "current  image    : " << image_cur.at<cv::Vec3b>(j, i) << "cur img depth val : " << image_cur.at<double>(cv::Point(j, i)) << "\n";
                    cout << "previous  image   : " << image_pre.at<cv::Vec3b>(j, i) << "pre img depth val : " << image_pre.at<double>(cv::Point(j, i)) << "\n";
                    cout << "abs-diff  image   : " << differenceImage.at<cv::Vec3b>(j, i) << "dif img depth val : " << differenceImage.at<double>(cv::Point(j, i)) << "\n";
                    cout << "threshholöd image : " << thresholdImage.at<cv::Vec3b>(j, i) << "thr img depth val : " << thresholdImage.at<double>(cv::Point(j, i)) << "\n";
                    cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
                }
            }
        /*
                for(int j=0; j<image_cur.rows; ++j)
                {
                    if(count_diff > 150)
                    {
                        break;
                    }
                        for(int i=0; i<image_cur.cols; ++i)
                        {
                            int depth = image_cur.at<short int>(cv::Point(j,i));
                            if(depth < 0.6)
                            {
                                cout<<"##############something within the range infront of the camera...########################\n";
                                if(image_cur.at<cv::Vec3b>(j,i) != image_pre.at<cv::Vec3b>(j,i))
                                {
                                    cout<<"i : "<<i<<" ... j ...
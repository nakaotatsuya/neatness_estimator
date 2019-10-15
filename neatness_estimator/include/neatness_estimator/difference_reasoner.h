#ifndef _NEATNESS_ESTIMATOR_DIFFERENCE_REASONER_H_
#define _NEATNESS_ESTIMATOR_DIFFERENCE_REASONER_H_

#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include <jsk_recognition_msgs/Histogram.h>
#include <jsk_recognition_msgs/ColorHistogram.h>
#include <jsk_recognition_msgs/ColorHistogramArray.h>
#include <jsk_recognition_msgs/ClusterPointIndices.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <std_srvs/SetBool.h>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl_msgs/PointIndices.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/io.h>
#include <pcl/point_types_conversion.h>
#include <pcl/point_types.h>
#include <pcl/filters/extract_indices.h>
/* #include <pcl/filters/uniform_sampling.h> */
#include <pcl/keypoints/uniform_sampling.h>
#include <pcl/features/vfh.h>
#include <pcl/features/cvfh.h>

#include <pcl/features/normal_3d_omp.h>
/* #include <pcl/features/shot_omp.h> */
#include <pcl/features/shot.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.hpp>

#include <mutex>
#include <boost/filesystem.hpp>

#include <jsk_recognition_utils/pcl/color_histogram.h>
#include <jsk_pcl_ros/region_adjacency_graph.h>

namespace neatness_estimator
{
  class DifferenceReasoner : public nodelet::Nodelet
  {
  public:

  protected:

    // functions

    virtual void onInit();

    virtual bool service_callback(std_srvs::SetBool::Request& req,
                                  std_srvs::SetBool::Response& res);

    virtual bool get_read_dirs(std::string& current_dir, std::string& prev_dir);

    virtual bool read_data(std::string& current_dir, std::string& prev_dir);

    virtual bool compute_histograms
      (const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& rgb_cloud,
       jsk_recognition_msgs::ClusterPointIndices::ConstPtr& input_indices,
       jsk_recognition_msgs::ColorHistogramArray& color_histogram_array,
       std::vector<jsk_recognition_msgs::Histogram>& geometry_histogram_array);

    virtual bool compute_color_histogram
      (const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& rgb_cloud,
       jsk_recognition_msgs::ColorHistogram& color_histogram);

    virtual bool compute_geometry_histogram
      (const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& rgb_cloud,
       jsk_recognition_msgs::Histogram& geometry_histogram);


    // variables

    ros::NodeHandle nh_;

    ros::NodeHandle pnh_;

    ros::ServiceServer server_;

    boost::mutex mutex_;

    std::string prefix_ = "./";

    std::map<std::string, std::string> topics_;

    std::string cloud_topic_ = "/openni_camera/point_cloud/cloud_registered/remote";

    std::string image_topic_ = "/openni_camera/rgb/image_rect_color";

    std::string cluster_topic_ = "/multi_euclidean_clustering/output_indices";

    jsk_recognition_msgs::ClusterPointIndices::ConstPtr current_cluster_;

    sensor_msgs::PointCloud2::ConstPtr current_cloud_;

    sensor_msgs::Image::ConstPtr current_image_;

    jsk_recognition_msgs::ClusterPointIndices::ConstPtr prev_cluster_;

    sensor_msgs::PointCloud2::ConstPtr prev_cloud_;

    sensor_msgs::Image::ConstPtr prev_image_;

    bool debug_view_ = false;

    int bin_size_ = 10;

    double white_threshold_ = 0.3;

    double black_threshold_ = 0.2;

    double normal_search_radius_ = 0.01;

    // 0: HUE, 1: HUE_AND_SATURATION
    jsk_recognition_utils::HistogramPolicy histogram_policy_ = jsk_recognition_utils::HUE;

  private:

  };

} // namespace neatness_estimator

#endif

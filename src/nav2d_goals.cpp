  #include <ros/ros.h>
  #include <move_base_msgs/MoveBaseAction.h>
  #include <actionlib/client/simple_action_client.h>
  
  typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
  
  int main(int argc, char** argv){
    ros::init(argc, argv, "nav2d_goals");
 
    //tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);
  
    //wait for the action server to come up
    while(!ac.waitForServer(ros::Duration(5.0))){
      ROS_INFO("Waiting for the move_base action server to come up");
    }
  
    move_base_msgs::MoveBaseGoal goal;
  
    //we'll send a goal to the robot to move 1 meter forward
    goal.target_pose.header.frame_id = "base_link";
    goal.target_pose.header.stamp = ros::Time::now();
  

    float xg[3] = {3.563, 3.209, -0.342};
    float yg[3] = {3.332,-3.598, -3.598};
    float wg[3] = {0.722, -1.406,-2.490};
 
    for( unsigned int i = 0; i < sizeof(xg)/sizeof(xg[0]); i++ )
    {
        goal.target_pose.pose.position.x = xg[i];
        goal.target_pose.pose.position.y = yg[i];
        goal.target_pose.pose.orientation.w = wg[i];
  
        ROS_INFO("Sending goal %d", i+1);
        ac.sendGoal(goal);

  
        ac.waitForResult();

        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
          ROS_INFO("Hooray, the base reached Checkpoint %d", i+1);
        else
          ROS_INFO("The base failed to read Checkpoint %d", i+1);

    }
  
    return 0;
   }

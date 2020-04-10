; Auto-generated. Do not edit!


(cl:in-package pick_ball_mbot_msgs-srv)


;//! \htmlinclude void_obstacle-request.msg.html

(cl:defclass <void_obstacle-request> (roslisp-msg-protocol:ros-message)
  ((obstacle
    :reader obstacle
    :initarg :obstacle
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass void_obstacle-request (<void_obstacle-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <void_obstacle-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'void_obstacle-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pick_ball_mbot_msgs-srv:<void_obstacle-request> is deprecated: use pick_ball_mbot_msgs-srv:void_obstacle-request instead.")))

(cl:ensure-generic-function 'obstacle-val :lambda-list '(m))
(cl:defmethod obstacle-val ((m <void_obstacle-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pick_ball_mbot_msgs-srv:obstacle-val is deprecated.  Use pick_ball_mbot_msgs-srv:obstacle instead.")
  (obstacle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <void_obstacle-request>) ostream)
  "Serializes a message object of type '<void_obstacle-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'obstacle) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <void_obstacle-request>) istream)
  "Deserializes a message object of type '<void_obstacle-request>"
    (cl:setf (cl:slot-value msg 'obstacle) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<void_obstacle-request>)))
  "Returns string type for a service object of type '<void_obstacle-request>"
  "pick_ball_mbot_msgs/void_obstacleRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'void_obstacle-request)))
  "Returns string type for a service object of type 'void_obstacle-request"
  "pick_ball_mbot_msgs/void_obstacleRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<void_obstacle-request>)))
  "Returns md5sum for a message object of type '<void_obstacle-request>"
  "94e2952797301ac06963adb1824707fa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'void_obstacle-request)))
  "Returns md5sum for a message object of type 'void_obstacle-request"
  "94e2952797301ac06963adb1824707fa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<void_obstacle-request>)))
  "Returns full string definition for message of type '<void_obstacle-request>"
  (cl:format cl:nil "bool obstacle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'void_obstacle-request)))
  "Returns full string definition for message of type 'void_obstacle-request"
  (cl:format cl:nil "bool obstacle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <void_obstacle-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <void_obstacle-request>))
  "Converts a ROS message object to a list"
  (cl:list 'void_obstacle-request
    (cl:cons ':obstacle (obstacle msg))
))
;//! \htmlinclude void_obstacle-response.msg.html

(cl:defclass <void_obstacle-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass void_obstacle-response (<void_obstacle-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <void_obstacle-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'void_obstacle-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pick_ball_mbot_msgs-srv:<void_obstacle-response> is deprecated: use pick_ball_mbot_msgs-srv:void_obstacle-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <void_obstacle-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pick_ball_mbot_msgs-srv:result-val is deprecated.  Use pick_ball_mbot_msgs-srv:result instead.")
  (result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <void_obstacle-response>) ostream)
  "Serializes a message object of type '<void_obstacle-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'result) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <void_obstacle-response>) istream)
  "Deserializes a message object of type '<void_obstacle-response>"
    (cl:setf (cl:slot-value msg 'result) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<void_obstacle-response>)))
  "Returns string type for a service object of type '<void_obstacle-response>"
  "pick_ball_mbot_msgs/void_obstacleResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'void_obstacle-response)))
  "Returns string type for a service object of type 'void_obstacle-response"
  "pick_ball_mbot_msgs/void_obstacleResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<void_obstacle-response>)))
  "Returns md5sum for a message object of type '<void_obstacle-response>"
  "94e2952797301ac06963adb1824707fa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'void_obstacle-response)))
  "Returns md5sum for a message object of type 'void_obstacle-response"
  "94e2952797301ac06963adb1824707fa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<void_obstacle-response>)))
  "Returns full string definition for message of type '<void_obstacle-response>"
  (cl:format cl:nil "bool result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'void_obstacle-response)))
  "Returns full string definition for message of type 'void_obstacle-response"
  (cl:format cl:nil "bool result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <void_obstacle-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <void_obstacle-response>))
  "Converts a ROS message object to a list"
  (cl:list 'void_obstacle-response
    (cl:cons ':result (result msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'void_obstacle)))
  'void_obstacle-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'void_obstacle)))
  'void_obstacle-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'void_obstacle)))
  "Returns string type for a service object of type '<void_obstacle>"
  "pick_ball_mbot_msgs/void_obstacle")
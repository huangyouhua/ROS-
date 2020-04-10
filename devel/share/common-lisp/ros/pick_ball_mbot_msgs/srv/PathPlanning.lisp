; Auto-generated. Do not edit!


(cl:in-package pick_ball_mbot_msgs-srv)


;//! \htmlinclude PathPlanning-request.msg.html

(cl:defclass <PathPlanning-request> (roslisp-msg-protocol:ros-message)
  ((Request
    :reader Request
    :initarg :Request
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass PathPlanning-request (<PathPlanning-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PathPlanning-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PathPlanning-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pick_ball_mbot_msgs-srv:<PathPlanning-request> is deprecated: use pick_ball_mbot_msgs-srv:PathPlanning-request instead.")))

(cl:ensure-generic-function 'Request-val :lambda-list '(m))
(cl:defmethod Request-val ((m <PathPlanning-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pick_ball_mbot_msgs-srv:Request-val is deprecated.  Use pick_ball_mbot_msgs-srv:Request instead.")
  (Request m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PathPlanning-request>) ostream)
  "Serializes a message object of type '<PathPlanning-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'Request) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PathPlanning-request>) istream)
  "Deserializes a message object of type '<PathPlanning-request>"
    (cl:setf (cl:slot-value msg 'Request) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PathPlanning-request>)))
  "Returns string type for a service object of type '<PathPlanning-request>"
  "pick_ball_mbot_msgs/PathPlanningRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PathPlanning-request)))
  "Returns string type for a service object of type 'PathPlanning-request"
  "pick_ball_mbot_msgs/PathPlanningRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PathPlanning-request>)))
  "Returns md5sum for a message object of type '<PathPlanning-request>"
  "2b99074ee17510311b29260db3a8ae84")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PathPlanning-request)))
  "Returns md5sum for a message object of type 'PathPlanning-request"
  "2b99074ee17510311b29260db3a8ae84")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PathPlanning-request>)))
  "Returns full string definition for message of type '<PathPlanning-request>"
  (cl:format cl:nil "bool Request~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PathPlanning-request)))
  "Returns full string definition for message of type 'PathPlanning-request"
  (cl:format cl:nil "bool Request~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PathPlanning-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PathPlanning-request>))
  "Converts a ROS message object to a list"
  (cl:list 'PathPlanning-request
    (cl:cons ':Request (Request msg))
))
;//! \htmlinclude PathPlanning-response.msg.html

(cl:defclass <PathPlanning-response> (roslisp-msg-protocol:ros-message)
  ((Result
    :reader Result
    :initarg :Result
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass PathPlanning-response (<PathPlanning-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PathPlanning-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PathPlanning-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pick_ball_mbot_msgs-srv:<PathPlanning-response> is deprecated: use pick_ball_mbot_msgs-srv:PathPlanning-response instead.")))

(cl:ensure-generic-function 'Result-val :lambda-list '(m))
(cl:defmethod Result-val ((m <PathPlanning-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pick_ball_mbot_msgs-srv:Result-val is deprecated.  Use pick_ball_mbot_msgs-srv:Result instead.")
  (Result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PathPlanning-response>) ostream)
  "Serializes a message object of type '<PathPlanning-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'Result) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PathPlanning-response>) istream)
  "Deserializes a message object of type '<PathPlanning-response>"
    (cl:setf (cl:slot-value msg 'Result) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PathPlanning-response>)))
  "Returns string type for a service object of type '<PathPlanning-response>"
  "pick_ball_mbot_msgs/PathPlanningResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PathPlanning-response)))
  "Returns string type for a service object of type 'PathPlanning-response"
  "pick_ball_mbot_msgs/PathPlanningResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PathPlanning-response>)))
  "Returns md5sum for a message object of type '<PathPlanning-response>"
  "2b99074ee17510311b29260db3a8ae84")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PathPlanning-response)))
  "Returns md5sum for a message object of type 'PathPlanning-response"
  "2b99074ee17510311b29260db3a8ae84")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PathPlanning-response>)))
  "Returns full string definition for message of type '<PathPlanning-response>"
  (cl:format cl:nil "bool Result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PathPlanning-response)))
  "Returns full string definition for message of type 'PathPlanning-response"
  (cl:format cl:nil "bool Result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PathPlanning-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PathPlanning-response>))
  "Converts a ROS message object to a list"
  (cl:list 'PathPlanning-response
    (cl:cons ':Result (Result msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'PathPlanning)))
  'PathPlanning-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'PathPlanning)))
  'PathPlanning-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PathPlanning)))
  "Returns string type for a service object of type '<PathPlanning>"
  "pick_ball_mbot_msgs/PathPlanning")
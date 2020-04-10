
(cl:in-package :asdf)

(defsystem "pick_ball_mbot_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "BallPositionStamp" :depends-on ("_package_BallPositionStamp"))
    (:file "_package_BallPositionStamp" :depends-on ("_package"))
  ))
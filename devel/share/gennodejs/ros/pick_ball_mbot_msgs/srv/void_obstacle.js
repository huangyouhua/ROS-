// Auto-generated. Do not edit!

// (in-package pick_ball_mbot_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class void_obstacleRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.obstacle = null;
    }
    else {
      if (initObj.hasOwnProperty('obstacle')) {
        this.obstacle = initObj.obstacle
      }
      else {
        this.obstacle = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type void_obstacleRequest
    // Serialize message field [obstacle]
    bufferOffset = _serializer.bool(obj.obstacle, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type void_obstacleRequest
    let len;
    let data = new void_obstacleRequest(null);
    // Deserialize message field [obstacle]
    data.obstacle = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'pick_ball_mbot_msgs/void_obstacleRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8e3182e1a5a09586299e547868ccbb8a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool obstacle
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new void_obstacleRequest(null);
    if (msg.obstacle !== undefined) {
      resolved.obstacle = msg.obstacle;
    }
    else {
      resolved.obstacle = false
    }

    return resolved;
    }
};

class void_obstacleResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.result = null;
    }
    else {
      if (initObj.hasOwnProperty('result')) {
        this.result = initObj.result
      }
      else {
        this.result = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type void_obstacleResponse
    // Serialize message field [result]
    bufferOffset = _serializer.bool(obj.result, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type void_obstacleResponse
    let len;
    let data = new void_obstacleResponse(null);
    // Deserialize message field [result]
    data.result = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'pick_ball_mbot_msgs/void_obstacleResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'eb13ac1f1354ccecb7941ee8fa2192e8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool result
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new void_obstacleResponse(null);
    if (msg.result !== undefined) {
      resolved.result = msg.result;
    }
    else {
      resolved.result = false
    }

    return resolved;
    }
};

module.exports = {
  Request: void_obstacleRequest,
  Response: void_obstacleResponse,
  md5sum() { return '94e2952797301ac06963adb1824707fa'; },
  datatype() { return 'pick_ball_mbot_msgs/void_obstacle'; }
};

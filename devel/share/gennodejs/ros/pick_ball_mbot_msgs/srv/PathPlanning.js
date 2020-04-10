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

class PathPlanningRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Request = null;
    }
    else {
      if (initObj.hasOwnProperty('Request')) {
        this.Request = initObj.Request
      }
      else {
        this.Request = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PathPlanningRequest
    // Serialize message field [Request]
    bufferOffset = _serializer.bool(obj.Request, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PathPlanningRequest
    let len;
    let data = new PathPlanningRequest(null);
    // Deserialize message field [Request]
    data.Request = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'pick_ball_mbot_msgs/PathPlanningRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ff201b53401f8d1221f1f88bb9daa999';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool Request
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PathPlanningRequest(null);
    if (msg.Request !== undefined) {
      resolved.Request = msg.Request;
    }
    else {
      resolved.Request = false
    }

    return resolved;
    }
};

class PathPlanningResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Result = null;
    }
    else {
      if (initObj.hasOwnProperty('Result')) {
        this.Result = initObj.Result
      }
      else {
        this.Result = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PathPlanningResponse
    // Serialize message field [Result]
    bufferOffset = _serializer.bool(obj.Result, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PathPlanningResponse
    let len;
    let data = new PathPlanningResponse(null);
    // Deserialize message field [Result]
    data.Result = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'pick_ball_mbot_msgs/PathPlanningResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '85ed39ee8c4e8f1c21743e6fe4dd523e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool Result
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PathPlanningResponse(null);
    if (msg.Result !== undefined) {
      resolved.Result = msg.Result;
    }
    else {
      resolved.Result = false
    }

    return resolved;
    }
};

module.exports = {
  Request: PathPlanningRequest,
  Response: PathPlanningResponse,
  md5sum() { return '2b99074ee17510311b29260db3a8ae84'; },
  datatype() { return 'pick_ball_mbot_msgs/PathPlanning'; }
};

//
// Copyright (C) Microsoft. All rights reserved.
//

var ffi = require('ffi');
var ref = require('ref');
var ArrayType = require('ref-array');

var UInt32Array = ArrayType(ref.types.uint32);

var addon = ffi.Library("./Output/Debug/Addon", {
  'GetEdgeInstances': [ 'int', [UInt32Array, 'uint32'] ]
});

var arg = new UInt32Array(3);
arg[0] = 1;
arg[1] = 2;
arg[2] = 3;

var count = addon.GetEdgeInstances(null, 0);
var arg = new UInt32Array(count);
arg.length = addon.GetEdgeInstances(arg, arg.length);

for (var i = 0; i < arg.length; i++)
{
    console.log(arg[i]);
}
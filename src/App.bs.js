// Generated by BUCKLESCRIPT VERSION 4.0.3, PLEASE EDIT WITH CARE
'use strict';

var Main$Rembrant = require("./Main.bs.js");
var Rembrandt$Rembrant = require("./Rembrandt.bs.js");

function update(model, action) {
  if (action.tag) {
    return model - action[0] | 0;
  } else {
    return model + action[0] | 0;
  }
}

Rembrandt$Rembrant.run((function (model, _) {
        return Main$Rembrant.div(undefined, undefined, /* :: */[
                    Main$Rembrant.text(String(model)),
                    /* [] */0
                  ], /* () */0);
      }), 42, update);

exports.update = update;
/*  Not a pure module */

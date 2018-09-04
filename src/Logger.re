/* TODO: date, action */
let loggerMiddleWare = (oldModel: 'model, newModel: 'model, action: 'action): unit => {
  Js.log("----------------------------");
  Js.log2("action", action);
  Js.log2("old model", oldModel);
  Js.log2("new model", newModel);
  Js.log("----------------------------");
}
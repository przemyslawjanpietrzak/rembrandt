module Elements = {
  type node = Common.node;
  let div = Common.div;
  let span = Common.span;
  let button = Common.button;
  let input = Common.input;
  let text = Common.text;
  let form = Common.form;
}

module Commands = {
  type command('a) = Command.command('a);
  let null = Command.null;
  let action = Command.action;
  let run = Command.run;
}

module Forms = {
  let getValue = Forms.getValue;
}

module MiddleWares = {
  let logger = Logger.loggerMiddleWare;
}

let run = Run.run;

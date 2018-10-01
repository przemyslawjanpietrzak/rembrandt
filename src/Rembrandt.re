module Elements = {
  type node = ElementsTypes.node;
  let div = Div.div;
  let span = Span.span;
  let button = Button.button;
  let input = Input.input;
  let text = Text.text;
  let form = FormElement.form;
  let a = A.a;
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
  let logger = Logger.loggerMiddleware;
}

let run = Run.run;

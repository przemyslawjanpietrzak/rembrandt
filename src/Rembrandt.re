module Elements = {
  type node = ElementsTypes.node;
  let div = Div.div;
  let span = Span.span;
  let button = Button.button;
  let input = Input.input;
  let text = Text.text;
  let form = FormElement.form;
  let a = A.a;
  let h1 = H.h1;
  let h2 = H.h2;
  let h3 = H.h3;
  let h4 = H.h4;
  let h5 = H.h5;
  let shadowRoot = ShadowRoot.shadowRoot;
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

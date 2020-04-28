open ElementFactory;
open ElementsTypes;
open Dom;

let h1 =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~onClick: eventHandler=defaultHandler,
      ~children,
      _rest,
    )
    : node =>
  generateNode(~name=H1, ~id, ~_class, ~style, ~key, ~onClick, ~children, ());

let h2 =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~onClick: eventHandler=defaultHandler,
      ~children,
      _rest,
    )
    : node =>
  generateNode(~name=H2, ~id, ~_class, ~style, ~key, ~onClick, ~children, ());

let h3 =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~onClick: eventHandler=defaultHandler,
      ~children,
      _rest,
    )
    : node =>
  generateNode(~name=H3, ~id, ~_class, ~style, ~key, ~onClick, ~children, ());

let h4 =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~onClick: eventHandler=defaultHandler,
      ~children,
      _rest,
    )
    : node =>
  generateNode(~name=H4, ~id, ~_class, ~style, ~key, ~onClick, ~children, ());

let h5 =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~onClick: eventHandler=defaultHandler,
      ~children,
      _rest,
    )
    : node =>
  generateNode(~name=H5, ~id, ~_class, ~style, ~key, ~onClick, ~children, ());

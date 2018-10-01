open ElementFactory;
open ElementsTypes;
open Dom;

let a =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~href="",
      ~onClick: eventHandler=defaultHandler,
      ~children,
      _rest,
    )
    : node =>
  generateNode(
    ~name=A,
    ~id,
    ~_class,
    ~style,
    ~key,
    ~href,
    ~onClick,
    ~children,
    (),
  );

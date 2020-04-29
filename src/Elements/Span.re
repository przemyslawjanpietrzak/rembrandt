open ElementFactory;
open ElementsTypes;
open Dom;

let span =
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
  generateNode(
    ~name=SPAN,
    ~id,
    ~_class,
    ~style,
    ~key,
    ~onClick,
    ~children,
    (),
  );

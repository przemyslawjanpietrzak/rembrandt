open ElementFactory;
open ElementsTypes;
open Dom;

let div =
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
    ~name=DIV,
    ~id,
    ~_class,
    ~style,
    ~key,
    ~onClick,
    ~children,
    (),
  );

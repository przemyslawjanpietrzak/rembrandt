open Jest;
open Main;
open VirtualDom;

/* describe("setPositions", () => {
    open Expect;

    test("simple node", () =>
        setPositions(~node=<div></div>, ~initialPosition=0)
        |> expect
        |> toEqual(1))

    test("node with child", () =>
        setPositions(~node=<div><div/></div>, ~initialPosition=0)
        |> expect
        |> toEqual(2))

    test("more complex node tree", () => {
        let node = <div><div><div/></div><div/></div>;
        setPositions(~node=node, ~initialPosition=0)
        |> expect
        |> toEqual(6);

        node.position |> expect |> toBe(6)
    });

}); */

describe("walker - basic", () => {
  open Expect;

  test("the same element should have empty diff", () =>
    walker(
      ~oldNode=<div></div>,
      ~newNode=Some(<div></div>),
      ~patches=Hashtbl.create(10000),
      ~index=0,
    )
    |>Hashtbl.length
    |> expect
    |> toEqual(0))

  test("props", () => {
    let diff = walker(
      ~oldNode=<div></div>,
      ~newNode=Some(<div id="value"></div>),
      ~patches=Hashtbl.create(10000),
      ~index=0,
    );

    Hashtbl.find(diff, 0)
      |> expect
      |> toEqual({ patchType: "props", attributes: Some([("id", "value")]), content: None })
  });

  test("replace", () => {
    let diff = walker(
      ~oldNode=<div></div>,
      ~newNode=Some(text("42")),
      ~patches=Hashtbl.create(10000),
      ~index=0,
    );

    Hashtbl.find(diff, 0)
      |> expect
      |> toEqual({ patchType: "replace", attributes: None, content: Some(text("42")) })
  });

  test("text", () => {
    let diff = walker(
      ~oldNode=text("41"),
      ~newNode=Some(text("42")),
      ~patches=Hashtbl.create(10000),
      ~index=0,
    );

    Hashtbl.find(diff, 0)
      |> expect
      |> toEqual({ patchType: "text", attributes: None, content: Some(text("42")) })
  });

});


describe("walker - advanced", () => {
  open Expect;

  test("change children attributes", () => {
    let oldNode = <div>
        <div _class="old1"/>
        <div _class="old2"/>
        <div _class="old3"/>
    </div>
    let _ = setPositions(~node=oldNode, ~initialPosition=0);
    let newNode = <div>
      <div _class="new1"/>
      <div _class="new2"/>
      <div _class="new3"/>
    </div>
    let _ = setPositions(~node=newNode, ~initialPosition=0);

    let diff = walker(
      ~oldNode=oldNode,
      ~newNode=Some(newNode),
      ~patches=Hashtbl.create(10000),
      ~index=0,
    );

    diff
      |>Hashtbl.length
      |> expect
      |> toEqual(3)

    Hashtbl.find(diff, 1)
      |> expect
      |> toEqual({ patchType: "props", attributes: Some([("class", "new1")]), content: None })

    Hashtbl.find(diff, 2)
      |> expect
      |> toEqual({ patchType: "props", attributes: Some([("class", "new2")]), content: None })

    Hashtbl.find(diff, 3)
      |> expect
      |> toEqual({ patchType: "props", attributes: Some([("class", "new3")]), content: None })
  });

   test("replace generation", () => {
      let oldNode = <div>
        <div _class="old1"/>
      </div>;
      let _ = setPositions(~node=oldNode, ~initialPosition=0);
      let newNode = <div>
        { text("42") }
      </div>;
      let _ = setPositions(~node=newNode, ~initialPosition=0);
      let diff = walker(
        ~oldNode=oldNode,
        ~newNode=Some(newNode),
        ~patches=Hashtbl.create(10000),
        ~index=0,
      );

      diff
        |>Hashtbl.length
        |> expect
        |> toEqual(1)

      Hashtbl.find(diff, 1)
        |> expect
        |> toEqual({ patchType: "replace", attributes: None, content: Some(text("42")) })

    });

    test("replace generation", () => {
      let oldNode = <div>
        <div _class="old1"/>
      </div>;
      let _ = setPositions(~node=oldNode, ~initialPosition=0);
      let newNode = <div>
        { text("42") }
        { text("43") }
      </div>;
      let _ = setPositions(~node=newNode, ~initialPosition=0);
      let diff = walker(
        ~oldNode=oldNode,
        ~newNode=Some(newNode),
        ~patches=Hashtbl.create(10000),
        ~index=0,
      );

      diff
        |>Hashtbl.length
        |> expect
        |> toEqual(2)

      Hashtbl.find(diff, 1)
        |> expect
        |> toEqual({ patchType: "replace", attributes: None, content: Some(text("42")) })

    });
});

/* describe("diffProps", () => {
  open Expect;

  test("the same nodes should return empty list", () =>
    diffProps(<div></div>, <div></div>)
    |> expect
    |> toEqual([]))

  test("removed class return empty string", () =>
    diffProps(<div _class="value"></div>, <div></div>)
    |> expect
    |> toEqual([("class", "")]))

  test("added class return added key and value", () =>
    diffProps(<div></div>, <div _class="value"></div>)
    |> expect
    |> toEqual([("class", "value")]))

  test("added attribures return this attributes", () =>
    diffProps(<div></div>, <div _class="value" id="id-value"></div>)
    |> expect
    |> toEqual([("id", "id-value"), ("class", "value")]))

}); */

/* describe("getPatch", () => {
  open Expect;

  test("the same nodes should returns empty list", () =>
    getPatch(<div></div>, Some(<div></div>))
    |> expect
    |> toEqual([]))

  test("the same text nodes should returns empty list", () =>
    getPatch(text("42"), Some(text("42")))
    |> expect
    |> toEqual([]))

  test("different text nodes should returns text patch", () =>
    getPatch(text("42"), Some(text("43")))
    |> expect
    |> toEqual([{
        patchType: "text",
        content: Some(text("43")),
        attributes: None
    }]))

  test("different nodes types should returns replace patch", () =>
    getPatch(<div></div>, Some(text("42")))
    |> expect
    |> toEqual([{
        patchType: "replace",
        content: Some(text("42")),
        attributes: None
    }]))

  test("the same nodes with different attributes should returns replace patch", () =>
    getPatch(<div _class="42"></div>, Some(<div _class="43"></div>))
    |> expect
    |> toEqual([{
        patchType: "props",
        content: None,
        attributes: Some([("class", "43")])
    }]))

}); */

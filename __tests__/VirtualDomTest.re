open Jest;
open Main;
open VirtualDom;

describe("diffProps", () => {
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

});

describe("getPatch", () => {
  open Expect;

  test("the same nodes should returns empty list", () =>
    getPatch(<div></div>, Some(<div></div>))
        |> expect
        |> toEqual([])
  )

  test("the same text nodes should returns empty list", () =>
    getPatch(text("42"), Some(text("42")))
        |> expect
        |> toEqual([])
  )

  test("different text nodes should returns text patch", () =>
    getPatch(text("42"), Some(text("43")))
        |> expect
        |> toEqual([{
            patchType: "text",
            content: Some(text("43")),
            attributes: None
        }])
  )

  test("different nodes types should returns replace patch", () =>
    getPatch(<div></div>, Some(text("42")))
        |> expect
        |> toEqual([{
            patchType: "replace",
            content: Some(text("42")),
            attributes: None
        }])
  )

  test("the same nodes with different attributes should returns replace patch", () =>
    getPatch(<div _class="42"></div>, Some(<div _class="43"></div>))
        |> expect
        |> toEqual([{
            patchType: "props",
            content: None,
            attributes: Some([("class", "43")])
        }])
  )

});



/* describe("walker", () => {
  open Expect;

  let oldNode = <div></div>;
  let newNode = Some(<div></div>);

  test("toBe", () =>
  walker(~oldNode=oldNode, ~newNode=newNode, ~index=0)
    |> expect
    |> toEqual([[{ patchType: "replace", content: None, attributes: Some([]) }]]))

  test("toBe", () =>
    walker(
      ~oldNode=<div></div>,
      ~newNode=None,
      ~index=0,
    )
      |> List.flatten
      |> expect
      |> toEqual([]))

  test("toBe", () =>
      walker(
        ~oldNode=<div>{ text("43") }</div>,
        ~newNode=Some(<div>{ text("43") }</div>),
        ~index=0,
      )
        |> List.flatten
        |> expect
        |> toEqual([]))
}); */



/* describe("Expect.Operators", () => {
    open Expect;
    open! Expect.Operators;

    test("==", () =>
      expect(1 + 2) === 3)
  }
); */
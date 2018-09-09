open Jest;

open Common;

open Diff;
open ListDiff;

describe("Test diff algorithm", () => {
  open Expect;

  test("Node replacing", () => {
    let updatedNode = <span key="2" />;
    let oldNode = <div> <div key="1" /> <div key="2" /> <div key="3" /> </div>;
    let newNode = <div> <div key="1" /> updatedNode <div key="3" /> </div>;

    let diff = getDiff(oldNode, Some(newNode));
    let patch = diff |> Utils.IntMap.find(2);

    patch
    |> expect
    |> toEqual([
         {
           patchType: Replace,
           content: Some(updatedNode),
           attributes: None,
           moves: [],
         },
       ]);
  });

  test("Node propeties change", () => {
    let oldNode =
      <div>
        <div key="1" id="same" />
        <div key="2" id="old1" />
        <div key="3" id="old2" />
      </div>;
    let newNode =
      <div>
        <div key="1" id="same" />
        <div key="2" id="new1" />
        <div key="3" id="new2" />
      </div>;

    let diff = getDiff(oldNode, Some(newNode));

    let patch = diff |> Utils.IntMap.find(2);
    patch
    |> expect
    |> toEqual([
         {
           patchType: Props,
           content: None,
           attributes: Some([("id", "new1")]),
           moves: [],
         },
       ])
    |> ignore;

    let patch1 = diff |> Utils.IntMap.find(3);
    patch1
    |> expect
    |> toEqual([
         {
           patchType: Props,
           content: None,
           attributes: Some([("id", "new2")]),
           moves: [],
         },
       ]);
  });

  test("Node removing", () => {
    let oldNode =
      <div>
        <div key="1" />
        <div key="2"> <span key="0" /> <span key="1" /> </div>
        <div key="3" />
      </div>;
    let newNode = <div> <div key="1" /> <div key="2" /> <div key="3" /> </div>;

    let diff = getDiff(oldNode, Some(newNode));
    let patch = diff |> Utils.IntMap.find(2);
    patch
    |> expect
    |> toEqual([
         {
           patchType: Children,
           content: None,
           attributes: None,
           moves: [
             {index: 0, moveType: Remove, item: None},
             {index: 0, moveType: Remove, item: None},
           ],
         },
       ]);
  });

  test("Text replacing", () => {
    let oldNode = text("42");
    let newNode = text("43");

    let diff = getDiff(oldNode, Some(newNode));
    let patch = diff |> Utils.IntMap.find(0);
    patch
    |> expect
    |> toEqual([
         {
           patchType: Text,
           content: Some(text("43")),
           attributes: None,
           moves: [],
         },
       ]);
  });

  test("Reordering with keyed items", () => {
    let oldNode =
      <div id="old">
        <div key="1" />
        <div key="2" />
        <div key="3" _class="1" />
        <div key="4" />
        <div key="5" />
      </div>;

    let newNode =
      <div id="new">
        <div key="1" />
        <div key="3" />
        <div key="5" />
        <div key="4" />
        <div key="2" _class="2" />
      </div>;
    let diff = getDiff(oldNode, Some(newNode));
    let patch = diff |> Utils.IntMap.find(0);
    patch |> List.length |> expect |> toEqual(2) |> ignore;
    patch->List.nth(0)
    |> expect
    |> toEqual({
         patchType: Props,
         content: None,
         attributes: Some([("id", "new")]),
         moves: [],
       })
    |> ignore;
    patch->List.nth(1).patchType |> expect |> toEqual(Children);
  });
});
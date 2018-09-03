open Jest;

open Common;

open Positions;
open Diff;
open ListDiff;

/* let getPatchType = patches => List.nth(patches, 0).patchType; */

describe("Test diff algorithm", () => {
  open Expect;

  test("Node replacing", () => {
    let updatedNode = <span key="2"/>;
    let oldNode = <div>
      <div key="1"/>
      <div key="2"/>
      <div key="3"/>
    </div>;
    let newNode = <div>
      <div key="1"/>
      { updatedNode }
      <div key="3"/>
    </div>;
    setPositions(oldNode, 0) |> ignore;
    setPositions(newNode, 0) |> ignore;

    let diff = getDiff(oldNode, Some(newNode));
    let patch = diff |> Utils.IntMap.find(2);

    patch |> expect |> toEqual([{
      patchType: Replace,
      content: Some(updatedNode),
      attributes: None,
      moves: [],
    }])
  });

  test("Node propeties change", () => {
    let oldNode = <div>
      <div key="1" id="same"/>
      <div key="2" id="old1" />
      <div key="3" id="old2" />
    </div>;
    let newNode = <div>
      <div key="1" id="same"/>
      <div key="2" id="new1"/>
      <div key="3"id="new2"/>
    </div>;
    setPositions(oldNode, 0) |> ignore;
    setPositions(newNode, 0) |> ignore;

    let diff = getDiff(oldNode, Some(newNode));

    let patch = diff |> Utils.IntMap.find(2);
    patch |> expect |> toEqual([{
      patchType: Props,
      content: None,
      attributes: Some([("id", "new1")]),
      moves: [],
    }]) |> ignore;

    let patch1 = diff |> Utils.IntMap.find(3);
    patch1 |> expect |> toEqual([{
      patchType: Props,
      content: None,
      attributes: Some([("id", "new2")]),
      moves: [],
    }]);
  });

  test("Node removing", () => {
    let oldNode = <div>
      <div key="1" />
      <div key="2">
        <span key="0" />
        <span key="1" />
      </div>
      <div key="3"  />
    </div>;
    let newNode = <div>
      <div key="1" />
      <div key="2"  />
      <div key="3"/>
    </div>;
    setPositions(oldNode, 0) |> ignore;
    setPositions(newNode, 0) |> ignore;

  let diff = getDiff(oldNode, Some(newNode));
  let patch = diff |> Utils.IntMap.find(2);
  patch |> expect |> toEqual([{
    patchType: Children,
    content: None,
    attributes: None,
    moves: [
      { index: 0, moveType: Remove, item: None },
      { index: 0, moveType: Remove, item: None },
    ],
  }]);

  })

  test("Text replacing", () => {
    let oldNode = text("42");
    let newNode = text("43");

    let diff = getDiff(oldNode, Some(newNode));
    let patch = diff |> Utils.IntMap.find(0);
    patch |> expect |> toEqual([{
      patchType: Text,
      content: Some(text("43")),
      attributes: None,
      moves: [],
    }]);
  })

  /* test("Reordering with keyed items", () => {
    let oldNode = <div id="old0">
      <div key="1" />
      <div key="2" />
      <div key="3"  />
    </div>;
    let newNode = <div id="new0">
      <div key="2"  />
      <div key="3"/>
      <div key="1" id="id"/>
    </div>;
    setPositions(oldNode, 0);
    setPositions(newNode, 0); */
    /* var oldRoot = el('ul', {id: 'list'}, [
      el('li', {key: 'a'}),
      el('li', {key: 'b'}),
      el('li', {key: 'c', style: 'shit'}),
      el('li', {key: 'd'}),
      el('li', {key: 'e'})
    ])

    var newRoot = el('ul', {id: 'lsit'}, [
      el('li', {key: 'a'}),
      el('li', {key: 'c'}),
      el('li', {key: 'e'}),
      el('li', {key: 'd'}),
      el('li', {key: 'b', name: 'Jerry'})
    ])

    var diffs = diff(oldRoot, newRoot)
    diffs[0].length.should.be.equal(2)
    diffs[2][0].type.should.equal(patch.PROPS)
    diffs[3][0].type.should.equal(patch.PROPS)

    diffs[2][0].props.should.deep.equal({name: 'Jerry'})
    diffs[3][0].props.should.deep.equal({style: void 555})

    diffs[0][0].type.should.equal(patch.PROPS)
    diffs[0][1].type.should.equal(patch.REORDER)
    diffs[0][1].moves.length.should.equal(4) */
  /* }) */

 
});
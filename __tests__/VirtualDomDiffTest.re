open Jest;
open Main;
open VirtualDom;
open ListDiff;

describe("Test diff algorithm", () => {
  open Expect;

  test("Node replacing", () => {
    let oldNode = <div>
      <div key="1"/>
      <div key="2"/>
      <div key="3"/>
    </div>;
    let newNode = <div>
      <div key="1"/>
      <span key="2"/>
      <div key="3"/>
    </div>;
    setPositions(oldNode, 0);
    setPositions(newNode, 0);

    let diff = getDiff(oldNode, Some(newNode));
    let patch = diff |> Utils.IntMap.find(2);

    patch.patchType |> expect |> toEqual(Replace)
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
    setPositions(oldNode, 0);
    setPositions(newNode, 0);

    let diff = getDiff(oldNode, Some(newNode));

    let patch = diff |> Utils.IntMap.find(2);
    patch.patchType |> expect |> toEqual(Props)
    patch.attributes |> expect |> toEqual(Some([("id", "new1")]))

    let patch1 = diff |> Utils.IntMap.find(3);
    patch1.patchType |> expect |> toEqual(Props)
    patch1.attributes |> expect |> toEqual(Some([("id", "new2")]))
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
    setPositions(oldNode, 0);
    setPositions(newNode, 0);

  let diff = getDiff(oldNode, Some(newNode));
  let patch = diff |> Utils.IntMap.find(2);
  patch.patchType |> expect |> toEqual(Children);
  patch.moves |> expect |> toEqual([
    { index: 0, moveType: Remove, item: None },
    { index: 0, moveType: Remove, item: None },
  ])
  })

  test("Text replacing", () => {
    let oldNode = text("42");
    let newNode = text("43");

    let diff = getDiff(oldNode, Some(newNode));
    let patch = diff |> Utils.IntMap.find(0);
    patch.patchType |> expect |> toEqual(Text);
    patch.content |> expect |> toEqual(Some(text("43")))
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
open Jest;

open Main;
open ListDiff;

type item = { key: string };

describe("walker - basic", () => {
  open Expect;

  test("Making map from list with string key", () => {
    let list = [
      <div key="1"/>
    ];
    let map = makeKeyIndexAndFree(list);
    map.keyIndex.should.be.deep.equal({
      id1: 0,
      id2: 1,
      id3: 2,
      id4: 3
    })
  })
});

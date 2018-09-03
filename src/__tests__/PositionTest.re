open Jest;

open Common;
open VirtualDom;

describe("set position", () => {
  open Expect;

  test("", () => {
    let node = <div>
      <div><span/></div>
      <div><span/></div>
      <div><span/></div>
      <div><span/></div>
    </div>
    node.position |> expect |> toBe(8);
  });

});

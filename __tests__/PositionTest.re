open Jest;

open Common;
open VirtualDom;

describe("Position", () => {
  open Expect;

  test("single node", () => {
    let node = <div/>;
    node.position |> expect |> toBe(0);
  });

  test("Mulitple nodes", () => {
    let node = <div>
      <div><span/></div>
      <div><span/></div>
      <div><span/></div>
      <div><span/></div>
    </div>
    node.position |> expect |> toBe(8);
  });

});

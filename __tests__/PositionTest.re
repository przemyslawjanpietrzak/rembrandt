open Jest;

open ElementsTypes;
// open VirtualDom;
open Div;
open Span;

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

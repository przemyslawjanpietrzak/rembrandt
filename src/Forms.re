let getValue: Dom.event => string = [%bs.raw
  {|
    function (e) {
      return e.target.value;
    }
  |}
];

let x = e: Dom.event => e#targer#value;
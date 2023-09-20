[@react.component]
let default: unit => React.element;

type metadata;
let meta: unit => metadata;

let loader: unit => Js_promise.t(Js_json.t);

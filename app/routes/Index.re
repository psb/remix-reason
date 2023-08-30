type metadata;

let meta = () => {
  [%bs.raw
   {|
    [{title: "New Remix App"},
    {name: "description", content: "Welcome to Remix!"}]
  |}];
};

[@react.component]
let default = () => {
  <div className="leading-7">
    <h1> {React.string("Welcome to Remix")} </h1>
    <ul>
      <li>
        <a
          target="_blank"
          href="https://remix.run/tutorials/blog"
          rel="noreferrer">
          {React.string("15m Quickstart Blog Tutorial")}
        </a>
      </li>
      <li>
        <a
          target="_blank"
          href="https://remix.run/tutorials/jokes"
          rel="noreferrer">
          {React.string("Deep Dive Jokes App Tutorial")}
        </a>
      </li>
      <li>
        <a target="_blank" href="https://remix.run/docs" rel="noreferrer">
          {React.string("Remix Docs")}
        </a>
      </li>
    </ul>
  </div>;
};

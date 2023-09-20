[@react.component]
let make = (~children) => {
  <>
    <nav className="px-10 pt-5">
      <Bindings.Link
        to_="/" prefetch="intent" className="text-2xl font-semibold">
        {React.string("Rick & Morty")}
        <span className="text-teal-500 ml-1"> {React.string("DB")} </span>
      </Bindings.Link>
    </nav>
    <main> children </main>
  </>;
};

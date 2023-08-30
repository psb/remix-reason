[%%bs.raw "import stylesheet from '~/tailwind.css';"];

type link;
let links = () => {
  [%bs.raw {|
    [{rel: "stylesheet", href: stylesheet}]
  |}];
};

type metadata = {
  charset: string,
  title: string,
  viewport: string,
};
let meta = () => {
  [|
    {
      charset: "utf-8",
      title: "New Remix App",
      viewport: "width=device-width,initial-scale=1",
    },
  |];
};

[@react.component]
let default = () => {
  <html lang="en">
    <head>
      <meta charSet="utf-8" />
      <meta name="viewport" content="width=device-width,initial-scale=1" />
      <Bindings.Meta />
      <Bindings.Links />
    </head>
    <body>
      <Layout>
        <Bindings.Outlet />
        <Bindings.ScrollRestoration />
        <Bindings.Scripts />
        <Bindings.LiveReload />
      </Layout>
    </body>
  </html>;
};

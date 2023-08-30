[@bs.module "@remix-run/react"] [@react.component]
external make:
  (
    ~to_: string,
    ~prefetch: string,
    ~className: string,
    ~children: React.element
  ) =>
  React.element =
  "Link";

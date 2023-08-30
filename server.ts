// import { createRequestHandler } from "@netlify/remix-adapter";
// import * as build from "@remix-run/dev/server-build";
// import { installGlobals } from "@remix-run/node";
// import sourceMapSupport from "source-map-support";

// sourceMapSupport.install();
// installGlobals();

// export const handler = createRequestHandler({
//   build,
//   mode: process.env.NODE_ENV,
// });

// From netlify remix template
// Import path interpreted by the Remix compiler
import { createRequestHandler } from "@netlify/remix-edge-adapter";
import * as build from "@remix-run/dev/server-build";

export default createRequestHandler({
  build,
  // process.env.NODE_ENV is provided by Remix at compile time
  mode: process.env.NODE_ENV,
});

export const config = {
  cache: "manual",
  path: "/*",
  // Let the CDN handle requests for static assets, i.e. ^/_assets/*$
  //
  // Add other exclusions here, e.g. "^/api/*$" for custom Netlify functions or
  // custom Netlify Edge Functions
  excluded_patterns: ["^/_assets/*$"],
};

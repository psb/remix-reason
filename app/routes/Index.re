type metadata;

let meta = () => {
  [%bs.raw
   {|
    [{title: "Remix and Reason"},
    {name: "description", content: "Remix and Reason"}]
  |}];
};

type json_body = {
  message: string,
  status: string,
};

type origin = {
  name: string,
  url: string,
};
type location = {
  name: string,
  url: string,
};
type url = string;

type character = {
  id: int, // The id of the character.
  name: string, // The name of the character.
  status: string, // The status of the character ('Alive', 'Dead' or 'unknown').
  species: string, // The species of the character.
  type_of_character: string, // The type or subspecies of the character.
  gender: string, // The gender of the character ('Female', 'Male', 'Genderless' or 'unknown').
  origin, // Name and link to the character's origin location.
  location, // Name and link to the character's last known location endpoint.
  image: url, // Link to the character's image. All images are 300x300px and most are medium shots or portraits since they are intended to be used as avatars.
  episode: array(url), // List of episodes in which this character appeared.
  url, // Link to the character's own URL endpoint.
  created: string // Time at which the character was created in the database.
};

type info = {
  count: int,
  pages: int,
  next: url,
  prev: option(url),
};

type characters_object_data = {
  info,
  results: array(character),
};

let decodeOrigin = (json): origin => {
  Json.Decode.{
    name: json |> field("name", string),
    url: json |> field("url", string),
  };
};

let decodeLocation = (json): location => {
  Json.Decode.{
    name: json |> field("name", string),
    url: json |> field("url", string),
  };
};

let decodeCharacter = (json): character =>
  Json.Decode.{
    id: json |> field("id", int),
    name: json |> field("name", string),
    status: json |> field("status", string),
    species: json |> field("species", string),
    type_of_character: json |> field("type", string),
    gender: json |> field("gender", string),
    origin: json |> field("origin", decodeOrigin),
    location: json |> field("location", decodeLocation),
    image: json |> field("image", string),
    episode: json |> field("episode", array(string)),
    url: json |> field("url", string),
    created: json |> field("created", string),
  };

let decodeInfo = json => {
  Json.Decode.{
    count: json |> field("count", int),
    pages: json |> field("pages", int),
    next: json |> field("next", string),
    prev: json |> field("prev", optional(string)),
  };
};

let decodeCharactersResultsObject = json => {
  Json.Decode.{
    info: json |> field("info", decodeInfo),
    results: json |> field("results", array(decodeCharacter)),
  };
};

let loader = () => {
  Js.Promise.(
    Fetch.fetch("https://rickandmortyapi.com/api/character")
    |> then_(Fetch.Response.json)
    |> then_(json => {
         //  let data = decodeCharacter(json);
         Js.log2("Loader", json);
         resolve(json);
       })
    |> catch(err => {
         //  let data = {message: "", status: "error"};
         Js.log2("Error", err);
         // let body = Json.Encode.(
         //       object_([("message", string(err)), ("status", string("error"))])
         //     );
         let body =
           Obj.magic({
             message: "Error fetching characters.",
             status: "error",
           });
         resolve(body);
       })
  );
};

let character = char => {
  <div
    key={Belt.Int.toString(char.id)}
    className="flex flex-col overflow-hidden rounded-lg  border bg-white">

      <Bindings.Link
        prefetch="intent"
        className="group relative block h-48 overflow-hidden bg-gray-100 md:h-64"
        to_={char.url}>
        <img
          src={char.image}
          alt=""
          className="absolute inset-0 h-full w-full object-cover object-center transition duration-2ßß group-hover:scale-110"
        />
      </Bindings.Link>
    </div>;
    // <div className="flex flex-1 flex-col p-4 sm:p-6">
    //   <h2 className="mb-2 text-lg font-semibold text-gray-800">
    //     <Link
    //       to={`movie/${movie.id}/comments`}
    //       prefetch="intent"
    //       className="transition duration-100 hover:text-indigo-500 active:text-indigo-600"
    //     >
    //       {movie.title}
    //     </Link>
    //   </h2>
    //   <p className="text-gray-500 line-clamp-3">{movie.overview}</p>
    // </div>
};

[@react.component]
let default = () => {
  let json = Bindings.DataLoader.useLoaderData();
  let data = json |> decodeCharactersResultsObject;
  Js.log2("useLoader", data);

  <div className="bg-white py-6 sm:py-8 lg:py-12">
    <div className="mx-auto max-w-screen-2xl px-4 md:px-8">
      <div className="mb-10 md:mb-16">
        <h2
          className="mb-4 text-center text-2xl fotn-bold text-gray-800 md:mb-6 lg:text-3xl">
          {React.string("Rick & Morty Characters")}
        </h2>
      </div>
    </div>
    <div
      className="grid gap-4 sm:grid-cols-2 md:gap-6 lg:grid-cols-3 xl:grid-cols-4 xl:gap-8">
      // {Belt.Array.map(data.results, res => character(res)) |> React.array}

        {Js_array.map(res => character(res), data.results) |> React.array}
      </div>
  </div>;
};

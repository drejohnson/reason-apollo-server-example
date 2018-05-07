[@bs.module] external uuid : unit => string = "uuid/v4";

type obj;

type todo = {
  .
  "guid": string,
  "description": string,
  "completed": bool,
};

type args = {. "input": todo};

type todos = array(todo);

type t = {
  .
  "Query": {. "getTodos": unit => todos},
  "Mutation": {
    .
    "addTodo": (obj, args) => todo,
    "updateTodo": (obj, args) => todo,
  },
};

[@bs.set]
external set_todo_description : (todo, string) => todo = "description";

[@bs.set] external set_todo_completed : (todo, bool) => todo = "completed";

let todos: todos = [||];

let resolvers: t = {
  "Query": {
    "getTodos": () => todos,
  },
  "Mutation": {
    "addTodo": (_obj, args) => {
      let input = args##input;
      let newTodo = {
        "guid": uuid(),
        "description": input##description,
        "completed": false,
      };
      todos |> Js.Array.push(newTodo) |> ignore;
      newTodo;
    },
    "updateTodo": (_obj, args) => {
      let input = args##input;
      let existingTodo =
        todos |> Js.Array.find(todo => todo##guid == input##guid);
      let todo =
        existingTodo
        |. Belt.Option.map(todo => {
             set_todo_description(todo, input##description) |> ignore;
             set_todo_completed(todo, input##completed) |> ignore;
             todo;
           })
        |. Belt.Option.getExn;
      todo;
    },
  },
};
let typeDefs = {|
  type Query {
    getTodos: [Todo]
  }
  type Mutation {
      addTodo(input: AddTodoInput!): Todo!,
      updateTodo(input: UpdateTodoInput!): Todo!
  }
  type Todo {
      guid: ID!,
      description: String!,
      completed: Boolean!
  }
  input AddTodoInput {
      description: String!
  }
  input UpdateTodoInput {
      guid: ID!,
      description: String!,
      completed: Boolean!
  }
|};
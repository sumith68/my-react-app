
- yarn global add bs-platform
- bsb -init my-react-app -theme react-hooks
- yarn add tailwindcss
- Create a file named src/styles.css and Copy 
  ```
      @tailwind base;
      @tailwind components;
      @tailwind utilities;
  ```
  to src/styles.css


- yarn run tailwind build src/styles.css -o src/output.css
- yarn add -D css-loader style-loader
- Copy https://www.npmjs.com/package/css-loader > webpack.config.js >

  ```
    module: {
    rules: [
      {
        test: /\.css$/i,
        use: ['style-loader', 'css-loader'],
      },
    ],
  }
  ```
  To webpack.config.js



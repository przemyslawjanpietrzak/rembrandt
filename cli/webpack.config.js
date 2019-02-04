const webpack = require('webpack');
const HtmlWebPackPlugin = require('html-webpack-plugin');

const path = require('path');

const isProduction = process.env.NODE_ENV === 'production';
const port = process.env.PORT || 4200 ;

module.exports = {
 entry: {
   main: './src/Main.bs.js',
 },
 output: {
   path: path.resolve(__dirname, './dist'),
   filename: '[name].[hash].js',
   publicPath: '/',
 },
 devtool: isProduction ? 'none' : 'source-map',
 module: {},
 plugins: [
   new HtmlWebPackPlugin({
     template: './src/index.html',
   }),
 ],
 devServer: {
   contentBase: path.join(__dirname, 'dist'),
   compress: false,
   port,
 }
};

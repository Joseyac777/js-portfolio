
const path = require('path');
const htmlWebpack = require('html-webpack-plugin')
const miniCssPlugin = require('mini-css-extract-plugin')
const copyWebpack = require('copy-webpack-plugin')
const cssMinimizer = require('css-minimizer-webpack-plugin')
const TerserPlugin = require('terser-webpack-plugin')
const Dotenv = require('dotenv-webpack')

module.exports = {
    entry: './src/index.js', //Elemento inicial del proyect
    output: {
        path: path.resolve( __dirname, 'dist'),
        filename: '[name].[contenthash].js',
        //Mover nuestros modulos con un hash y su extencion y query
        assetModuleFilename: 'assets/images/[hash][ext][query]',
        clean: true,
    },
    mode: 'production',
    resolve: {
        extensions: ['.js',],
        //Las alias nos optimizan las rutas de archivos
        alias: {
            '@utils': path.resolve(__dirname, 'src/utils/'),
            '@templates': path.resolve(__dirname, 'src/templates/'),
            '@styles': path.resolve(__dirname, 'src/styles/'),
            '@images': path.resolve(__dirname, 'src/assets/images/')
        }
    },
    module: {
        rules:[
            // reglas para este proyecto
            {
                //Que extenciones vamos a usar
                test: /\.m?js$/,
                exclude: /node_modules/,
                use: {
                    loader: 'babel-loader'
                }
            },
            {
                //Archivos de css que va a leer 
                test: /\.css|styl$/i,
                use: [miniCssPlugin.loader, 'css-loader', 'stylus-loader'],
            },
            {
                //optimisa las imagenes y las crea un hash
                test: /\.png/,
                type: 'asset/resource'
            },
            {
                //optimiza las font de la web Wolf
                test: /\.(woff|woff2)$/,
                use: {
                    loader: 'url-loader',
                    options: {
                        limit: 10000,
                        mimetype: "aplication/font/woff",
                        name: "[name].[contenthash].[ext]",
                        // EL NOMBRE INICIAL DEL ARCHIVO + SU EXTENSIÓN
                        // PUEDES AGREGARLE [name]hola.[ext] y el output del archivo seria 
                        // ubuntu-regularhola.woff
                        
                        outputPath: "./assets/fonts/",
                        // EL DIRECTORIO DE SALIDA (SIN COMPLICACIONES)

                        publicPath: "../assets/fonts/",
                        // EL DIRECTORIO PUBLICO (en dist)

                        esModule: false
                        // AVISAR EXPLICITAMENTE SI ES UN MODULO
                    }
                }
            }
        ]
    },
    plugins: [
        new htmlWebpack({
            inject: true,
            template: './public/index.html',
            filename: './index.html'
        }),
        new miniCssPlugin({
            filename: 'assets/[name].[contenthash].css'
        }),
        new copyWebpack({
            //Se uso para mover a dist para que en el template podamos con la ruta
            //mas corta assets/imagenes(name)
            //pero se cambio por la optimizacion de imagenes con hash
            patterns: [ //Elementos a usar 
                {
                    from: path.resolve(__dirname, "src", 'assets/images'), //Direccion
                    to: "assets/images" //A donde en la carpeta dist
                }
            ]
        }),
        new Dotenv(),
    ],
    optimization: {
        minimize: true,
        minimizer: [
          new cssMinimizer(),
          new TerserPlugin(),
        ]
    }
}




echo "EMBEDDABLE_URI=http://localhost:3000/#/en/embeddable" > .env

for d in */; do
   echo ".................. Compiling folder $d ..................."

     cd $d
     cp ../package.json ./package.json
     cp ../webpack.config.js ./webpack.config.js
     rm -rf build
     npm install
     npm run build
     #rm -rf node_modules
     rm webpack.config.js
     rm package.json
     rm package-lock.json
     rm pnpm-lock.yaml
    cd ..
done


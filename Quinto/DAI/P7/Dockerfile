FROM node:22
WORKDIR /app
COPY package.json /app
COPY . /app
ENV USER_DB=root
ENV PASS=example
ENV IN=production
ENV SECRET_KEY=secret_key
ENV DB_HOST=mongo
RUN npm ci --only=production && npm cache clean --force
CMD node tienda.js
EXPOSE 8000
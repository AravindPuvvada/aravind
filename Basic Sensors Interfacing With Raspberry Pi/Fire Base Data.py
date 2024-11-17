// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyC4n8l9wRhUqgcRmWtmO5f7rjdk4AVqagM",
  authDomain: "rpi-images-f1d81.firebaseapp.com",
  databaseURL: "https://rpi-images-f1d81-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "rpi-images-f1d81",
  storageBucket: "rpi-images-f1d81.appspot.com",
  messagingSenderId: "748154264731",
  appId: "1:748154264731:web:03ecb90e27110a8bab7a3e",
  measurementId: "G-5Z7DS54GT9"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);

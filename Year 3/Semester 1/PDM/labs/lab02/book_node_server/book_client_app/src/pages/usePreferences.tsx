import { useEffect } from 'react';
import {GetResult, Preferences} from '@capacitor/preferences';

export const usePreferencesSave = (user:String, token:String) => {
  useEffect(() => {
    insertIntolocalStorage(user, token);
  }, []);

  function insertIntolocalStorage(user: String, token: String) {
    (async () => {
      await Preferences.set({
        key: 'user',
        value: JSON.stringify({
          username: user, token: token,
        })
      });
    })();
  }
};

export const usePreferencesFind:() => Promise<GetResult> = (async () => {
  return await Preferences.get({ key: 'user' });
});

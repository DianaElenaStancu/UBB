import React, {useCallback, useContext, useEffect, useState} from 'react';
import { IonButton, IonContent, IonHeader, IonInput, IonLoading, IonPage, IonTitle, IonToolbar } from '@ionic/react';
import { RouteComponentProps } from 'react-router';
import {AuthContext} from './AuthProvider';
import { getLogger } from '../core';
import {Preferences} from "@capacitor/preferences";

const log = getLogger('Login');

interface LoginState {
    username2?: string;
    password?: string;
}
export const Login: React.FC<RouteComponentProps> = ({ history }) => {
    const { isAuthenticated, isAuthenticating, login, authenticationError, token, username } = useContext(AuthContext);
    const [state, setState] = useState<LoginState>({});
    const { username2,password } = state;
    const handlePasswwordChange = useCallback((e: any) => setState({
        ...state,
        password: e.detail.value || ''
    }), [state]);
    const handleUsernameChange = useCallback((e: any) => setState({
        ...state,
        username2: e.detail.value || ''
    }), [state]);
    const handleLogin = useCallback(() => {
        log('handleLogin...');
        login?.(username2, password);
    }, [username2, password]);
    log('render');
    useEffect(() => {
        log("****" + isAuthenticated + "****")
        if (isAuthenticated)
        {
            if(username2 !== undefined)
            {
                Preferences.set({
                    key: 'user',
                    value: JSON.stringify({
                        username: username2,token
                    })
                });
            }
            else
            {
                setState({
                    ...state,
                    username2: username
                })
            }
            log('redirecting to home');
            history.push('/');
        }
    }, [isAuthenticated, token]);
    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Login</IonTitle>
                </IonToolbar>
            </IonHeader>
            <IonContent>
                <IonInput
                    placeholder="Username"
                    value={username2}
                    onIonChange={handleUsernameChange}/>
                <IonInput
                    placeholder="Password"
                    value={password}
                    onIonChange={handlePasswwordChange}/>
                <IonLoading isOpen={isAuthenticating}/>
                {authenticationError && (
                    <div>{authenticationError.message || 'Failed to authenticate'}</div>
                )}
                <IonButton onClick={handleLogin}>Login</IonButton>
            </IonContent>
        </IonPage>
    );
};

import React, {useCallback, useEffect, useReducer, useState} from 'react';
import PropTypes from 'prop-types';
import { getLogger } from '../core';
import { login as loginApi } from './AuthApi';
import {Preferences} from "@capacitor/preferences";

const log = getLogger('AuthProvider');

type LoginFn = (username?: string, password?: string) => void;

export interface AuthState {
    authenticationError: Error | null;
    isAuthenticated: boolean;
    isAuthenticating: boolean;
    login?: LoginFn;
    pendingAuthentication?: boolean;
    username?: string;
    password?: string;
    token: string;
}

export const initialState: AuthState = {
    isAuthenticated: false,
    isAuthenticating: false,
    authenticationError: null,
    pendingAuthentication: false,
    token: '',};

export const AuthContext = React.createContext<AuthState>(initialState);

interface AuthProviderProps {
    children: PropTypes.ReactNodeLike,
}
export const AuthProvider: React.FC<AuthProviderProps> = ({ children }) => {
    const [state, setState] = useState<AuthState>(initialState);
    const { isAuthenticated, isAuthenticating, authenticationError, pendingAuthentication, token } = state;
    useEffect(getPreference,[isAuthenticated, token]);
    const login = useCallback<LoginFn>(loginCallback, []);
    useEffect(authenticationEffect, [pendingAuthentication]);
    const value = { isAuthenticated, login, isAuthenticating, authenticationError, token };
    log('render');
    return (
        <AuthContext.Provider value={value}>
            {children}
        </AuthContext.Provider>
    );
    function getPreference(){
        (async () => {
            const rez = await Preferences.get({ key: 'user' });
            if(rez.value)
            {
                setState({
                    ...state,
                    token: JSON.parse(rez.value).token,
                    username: JSON.parse(rez.value).username,
                    isAuthenticated: true
                })
            }
            return;
        })();
    }
    function loginCallback(username?: string, password?: string): void {
        log('login');
        setState({
            ...state,
            pendingAuthentication: true,
            username,
            password
        });
    }
    function authenticationEffect() {
        let canceled = false;
        authenticate();
        return () => {
            canceled = true;
        }

        async function authenticate() {
            if (!pendingAuthentication) {
                log('authenticate, !pendingAuthentication, return');
                return;
            }
            try {
                log('authenticate...');
                setState({
                    ...state,
                    isAuthenticating: true,
                });                const { username, password } = state;
                const { token } = await loginApi(username, password);
                if (canceled) {
                    return;
                }
                log('authenticate succeeded');
                setState({
                    ...state,
                    token,
                    pendingAuthentication: false,
                    isAuthenticated: true,
                    isAuthenticating: false,
                });
            } catch (error) {
                if (canceled) {
                    return;
                }
                log('authenticate failed');
                setState({
                    ...state,
                    authenticationError: error as Error,
                    pendingAuthentication: false,
                    isAuthenticating: false,
                });
            }
        }
    }
};

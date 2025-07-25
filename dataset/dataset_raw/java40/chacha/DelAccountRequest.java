/*
 * Copyright 2012 the original author or authors.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */
package org.chacha.client.command.account;

import java.io.IOException;

import org.chacha.client.command.JsonConvert;
import org.chacha.client.command.Request;
import org.chacha.util.JsonPojoMapper;

import com.fasterxml.jackson.core.JsonGenerationException;
import com.fasterxml.jackson.databind.JsonMappingException;

/**
 *  删除帐号请求命令
 *  @author: Fully
 */
public class DelAccountRequest extends Request implements JsonConvert{
    private static final String CMD="del";
    private AccountNameBody body;
    
    
    public DelAccountRequest(AccountNameBody body) {
        super.setOpt(CMD);
        this.body = body;
    }

    public DelAccountRequest() {
        super.setOpt(CMD);
    }

    public AccountNameBody getBody() {
        return body;
    }

    public void setBody(AccountNameBody body) {
        this.body = body;
    }

    @Override
    public String toJson() throws JsonMappingException,
            JsonGenerationException, IOException {
        return JsonPojoMapper.toJson(this,true);
    }

    @Override
    public void fromJson(String json) throws JsonMappingException,
            JsonGenerationException, IOException {
        DelAccountRequest r=(DelAccountRequest)JsonPojoMapper.fromJson(json, DelAccountRequest.class);
        this.setOpt(r.getOpt());
        this.setBody(r.getBody());
    }

    public static void main(String[] args){
        String[] nameArray=new String[]{"aaa","bbb","ccc"};
        AccountNameBody body=new AccountNameBody(nameArray);
        DelAccountRequest request=new DelAccountRequest(body);
        try{
            System.out.println(request.toJson());
        }catch(Exception e){
            e.printStackTrace();
        }
        //json转换为pojo
        DelAccountRequest r=new DelAccountRequest();
        try{
            r.fromJson(request.toJson());
            System.out.println(r.toJson());
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}

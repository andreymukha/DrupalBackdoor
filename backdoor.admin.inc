<?php

function admin_page_backdoor() {
  $key = variable_get('key');
  if(!empty($key)){
    $pass_access = t('На этой странице нет настроек');
  }else{
    $pass_access = drupal_get_form('admin_backdoor_form');
    $pass_access = drupal_render($pass_access);
  }
  return $pass_access;
}

function admin_backdoor_form ($form, &$form_state) {

  $form = array();

  $form['key'] = array(
    '#title' => t('Ключ для входа на защищённую страницу'),
    '#description' => t('Ключ вводится один раз, восстановить его невозможно, так что не потеряйте'),
    '#type' => 'password',
    '#maxlength' => 64,
    '#size' => 35,
    '#required' => TRUE
  );

  $form['bd_password'] = array(
    '#title' => t('Пароль для открытия ссылки'),
    '#description' => t('Пароль вводится один раз, восстановить его невозможно, так что не потеряйте'),
    '#type' => 'password',
    '#maxlength' => 64,
    '#size' => 35,
    '#required' => TRUE
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Отправить'),
  );

  return $form;
}

function admin_backdoor_form_validate ($form, &$form_state){
  $length_key = mb_strlen($form_state['values']['key']);
  $length_password = mb_strlen($form_state['values']['bd_password']);

  if ($length_key < 4){
    form_set_error('key', t('Длинна ключа должна быть не более 4-х символов'));
  }

  if ($length_password < 4){
    form_set_error('bd_password', t('Длинна пароля должна быть не более 4-х символов'));
  }

  if($form_state['values']['key'] == $form_state['values']['bd_password']){
    form_set_error('bd_password', t('Значения полей не должны совпадать!'));
  }

}

function admin_backdoor_form_submit ($form, &$form_state){
  $key = user_hash_password($form_state['values']['key']);
//  $password = user_hash_password($form_state['values']['bd_password']);
  $password = $form_state['values']['bd_password'];
  variable_set('key', $key);
  variable_set('bd_password', $password);
  drupal_set_message(t('Секретный ключ и пароль успешно сохранёны в базу данных'));
}
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using UnityEditor;
using UnityEngine;
using static Microsoft.MixedReality.GraphicsTools.MeshInstancer;

namespace Synergiz.Harbor.Player
{
    public class Menu_pokeball : MonoBehaviour
    {
        public GameObject prefab;
        GameObject pokeball;

        // Start is called before the first frame update
        void Start()
        {
        
        }

        // Update is called once per frame
        void Update()
        {
        
        }

        public void SpawnPokeBall() {
            if (pokeball == null)
            {
                this.CreatePokeBall();
            }
            else {
                Object.Destroy(pokeball);
                this.CreatePokeBall();
            }
        }

        public void CreatePokeBall()
        {
            float distance = 1.5f;
            Camera cam = Camera.main;
            Vector3 size = prefab.GetComponent<Renderer>().bounds.size;
            pokeball = Instantiate(prefab, Camera.main.ScreenToWorldPoint(new Vector3(Screen.width * 3/4 - size.x/2, Screen.height * 1/4 - size.y/2, 0) + cam.transform.forward * distance),
                    new Quaternion(0.0f, cam.transform.rotation.y, 0.0f, cam.transform.rotation.w)) as GameObject;
            Rigidbody rigidbody = pokeball.GetComponent<Rigidbody>();
            rigidbody.useGravity = false;
            rigidbody.isKinematic = true;
            pokeball.transform.SetParent(cam.transform);
        }
    }
}

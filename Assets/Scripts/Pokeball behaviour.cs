using GLTFast.Schema;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using UnityEngine;

namespace Synergiz.Harbor.Player
{
    public class Pokeballbehaviour : MonoBehaviour
    {
        public string pokeballType = "Pokeball";
        public float ballBonus = 0.5f;
        public bool isThrown = false;
        public bool hasHitPokemon = false;
        public bool hasHitHazard = false;
        private Coroutine rotateCoroutine;
        public Vector3 hitPoint;

        // Start is called before the first frame update
        void Start()
        {
        
        }

        // Update is called once per frame
        void Update()
        {

        }


        public void OnCollisionEnter(Collision collision)
        {
            Pokemonbehaviour pokemonbehaviour = collision.gameObject.GetComponent<Pokemonbehaviour>();
            if (pokemonbehaviour is null && this.isThrown)
            {
                this.hasHitHazard = true;
            }
            else
            {
                hitPoint = collision.transform.position;
                foreach (ContactPoint contact in collision.contacts)
                {
                    Debug.DrawRay(contact.point, contact.normal, UnityEngine.Color.white);
                }
            }
        }

        public void OnStartGrabbing() {
            Debug.Log("Grabbed");
            transform.SetParent(null);
            Rigidbody rigidbody = GetComponent<Rigidbody>();
            rigidbody.isKinematic = false;
            rigidbody.useGravity = true;
        }

        public void OnEndGrabbing()
        {
            this.isThrown = true;
        }

        public void triggerCatchingphase(GameObject pokemon)
        {
            this.hasHitPokemon = true;
            transform.localScale *= 1.5f;
            Rigidbody rigidbody = GetComponent<Rigidbody>();
            rigidbody.useGravity = false;
            rigidbody.isKinematic = true;

            if (rotateCoroutine is not null)
            {
                StopCoroutine(rotateCoroutine);
            }
            Vector3 direction = hitPoint - transform.position;
            Quaternion targetRotation = Quaternion.FromToRotation(transform.forward, direction);
            StartCoroutine(RotateObject(targetRotation, 1f));
        }

        private IEnumerator RotateObject(Quaternion targetRotation, float duration)
        {
            float timer = 0f;
            Quaternion startRotation = transform.rotation;

            while (timer < duration)
            {
                transform.rotation = Quaternion.Lerp(startRotation, targetRotation, timer / duration);
                timer += Time.deltaTime;
                yield return null;
            }

            // Ensure final scale is set exactly to target scale
            transform.rotation = targetRotation;
        }
    }
}